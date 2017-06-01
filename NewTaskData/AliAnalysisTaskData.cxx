#include <iostream>
#include <cstdlib>

// ROOT classes
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "TProfile.h"
#include "TExMap.h"
#include "TClonesArray.h"


// Alice analysis base class
#include "AliAnalysisTaskSE.h"


// Alice analysis additional classes
#include "AliAnalysisManager.h"
//#include "AliInputEventHandler.h"
// Alice AOD classes
#include "AliAODInputHandler.h"
//#include "AliAODHandler.h"


// Alice AOD tree classes
#include "AliVEvent.h"
#include "AliAODEvent.h"
#include "AliAODVertex.h"
#include "AliAODVZERO.h"
#include "AliAODZDC.h"
#include "AliCentrality.h"


// Alice PID classes
#include "AliAODPid.h"
//#include "AliAODpidUtil.h"
#include "AliPID.h"
//#include "AliPIDCombined.h"
#include "AliPIDResponse.h"


// This class
#include "AliAnalysisTaskData.h"


using std::cout;
using std::endl;

const float pi = 3.1415926535;


ClassImp(Event); // import class inheriting from TObject
ClassImp(Track); // import class inheriting from TObject
ClassImp(AliAnalysisTaskData); // import class inheriting from TObject



//------------------------------------------------------------------
AliAnalysisTaskData::AliAnalysisTaskData() : AliAnalysisTaskSE()
{
  // Default class constructor

  cout<<"Default class constructor called.  Prepare for fun analysis time!"<<endl;

  trigger = AliVEvent::kMB;

}



//--------------------------------------------------------------------------------------
AliAnalysisTaskData::AliAnalysisTaskData(const char *name) : AliAnalysisTaskSE(name)
{
  // Class Constructor with name

  cout<<"User defined class constructor called.  Prepare for fun analysis time!"<<endl;

  // Define input and output slots here
  // Input slot #0 works with a TChain
  DefineInput(0,TChain::Class());

  // Output slot #0 is reserved by the base class for AOD
  // Output slot #1 writes into a TH1 container
  DefineOutput(0,TTree::Class());
  DefineOutput(1,TList::Class());
  DefineOutput(2,TTree::Class());



  // user can change as needed
  trigger = AliVEvent::kMB;
  debug = 0;
  fbit = 16383;
  zvtxcut = 15.0;
  centcut = 5.0;
  nclscut = 60;
  dcacut = 3.5;
  outeta = 0.8;
  ineta = 0.5;
  ptmin = 0.2;
  ptmax = 5.0;

}



//---------------------------------------------------
void AliAnalysisTaskData::UserCreateOutputObjects()
{

  // Create output objects, like histograms - called once

  cout<<"UserCreateOutputObjects called, now making histrograms and things"<<endl;



  // -------------------------- //
  // --- create output list --- //
  // -------------------------- //

  fOutputList = new TList();
  fOutputList->SetName(GetName());
  fOutputList->SetOwner(kTRUE);



  // ------------------------- //
  // --- create histograms --- //
  // ------------------------- //



  fHistDCACOVerrors = new TH1F("fHistDCACOVerrors","",100,0.0,1.0);
  fOutputList->Add(fHistDCACOVerrors);



  fHistPt = new TH1F("fHistPt","",50,0.0,5.0);
  fHistPhi = new TH1F("fHistPhi","",63,0.0,6.3);
  fHistEta = new TH1F("fHistEta","",110,-1.1,1.1);
  fHistCharge = new TH1F("fHistCharge","",3,-1.5,1.5);
  fHistTPCncls = new TH1F("fHistTPCncls","",161,-0.5,160.5);
  fHistDedxTPC = new TH1F("fHistDedxTPC","",1000,-20,980);
  fHistDCAxy = new TH1F("fHistDCAxy","",350,-3.5,3.5);
  fHistDCAz = new TH1F("fHistDCAz","",350,-3.5,3.5);
  fOutputList->Add(fHistPt);
  fOutputList->Add(fHistPhi);
  fOutputList->Add(fHistEta);
  fOutputList->Add(fHistCharge);
  fOutputList->Add(fHistTPCncls);
  fOutputList->Add(fHistDedxTPC);
  fOutputList->Add(fHistDCAxy);
  fOutputList->Add(fHistDCAz);

  fHistZVtx = new TH1F("fHistZVtx","",80,-20,20);
  fHistZVtxD = new TH1F("fHistZVtxD","",100,-5,5);
  fHistCentTRK = new TH1F("fHistCentTRK","",100,0,100);
  fHistCentV0M = new TH1F("fHistCentV0M","",100,0,100);
  fOutputList->Add(fHistZVtx);
  fOutputList->Add(fHistZVtxD);
  fOutputList->Add(fHistCentTRK);
  fOutputList->Add(fHistCentV0M);
  fHistCentTRKkSel = new TH1F("fHistCentTRKkSel","",100,0,100);
  fHistCentV0MkSel = new TH1F("fHistCentV0MkSel","",100,0,100);
  fOutputList->Add(fHistCentTRKkSel);
  fOutputList->Add(fHistCentV0MkSel);



  // --------------------- //
  // --- now TTree ... --- //
  // --------------------- //

  cout<<"Now preparing event and track for tree"<<endl;

  fEvent = new Event();
  fTrackArrayGlobal = new TClonesArray("Track",3000);
  fTrackArrayHybrid = new TClonesArray("Track",3000);
  fTrackArrayTPCnly = new TClonesArray("Track",3000);

  cout<<"Now preparing tree"<<endl;

  fTree = new TTree("tree","tree");
  fTree->Branch("fEvent",&fEvent);
  fTree->Branch("fTrackGlobal","TClonesArray",&fTrackArrayGlobal);
  fTree->Branch("fTrackHybrid","TClonesArray",&fTrackArrayHybrid);
  fTree->Branch("fTrackTPCnly","TClonesArray",&fTrackArrayTPCnly);



  PostData(1,fOutputList);
  PostData(2,fTree);

  cout<<"Data now posted!"<<endl;

}



//----------------------------------------------
void AliAnalysisTaskData::UserExec(Option_t *) 
{

  // Main analyis loop, called for each event

  if(debug>0) cout<<"processing event with debug = "<<debug<<endl;

  // Analysis manager
  AliAnalysisManager *manager = AliAnalysisManager::GetAnalysisManager();
  if(!manager)
    {
      cout<<"FATAL: could not get Analysis Manager."<<endl;
      return;
    }

  // Input handler
  AliAODInputHandler *handler = (AliAODInputHandler *)manager->GetInputEventHandler();
  if(!handler)
    {
      cout<<"FATAL: could not get Input Handler."<<endl;
      return;
    }

  // AOD Event object from tree
  AliAODEvent *fAOD = dynamic_cast<AliAODEvent*>(InputEvent());
  if(!fAOD)
    {
      if(debug>-1) cout<<"ERROR: AOD event object not available. Discarding event..."<<endl;
      return;
    }

  ULong64_t offmask = handler->IsEventSelected();
  ULong64_t amb = AliVEvent::kMB;
  ULong64_t acn = AliVEvent::kCentral;
  ULong64_t asc = AliVEvent::kSemiCentral;

  if(debug>0) cout<<"offline trigger mask is "<<offmask<<endl;

  // Centrality object (from AOD)
  AliCentrality *fCentrality = fAOD->GetCentrality();
  if(!fCentrality)
    {
      if(debug>-1) cout<<"ERROR: Centrality object not available. Discarding event..."<<endl;
      return;
    }
  float centTRK = fCentrality->GetCentralityPercentile("TRK");
  float centV0M = fCentrality->GetCentralityPercentile("V0M");

  ULong64_t kSelected = amb|acn|asc;
  bool isPhysicsEvent = offmask & kSelected;

  ULong64_t onmask = fAOD->GetTriggerMask();

  // Ionut
  bool isMB = (onmask & (ULong64_t(1)<<1));
  bool isCentral = (onmask & (ULong64_t(1)<<4));
  bool isSemiCentral = (onmask & (ULong64_t(1)<<7));

  if(debug>0) cout<<"online trigger mask is "<<onmask<<endl;

  // ---
  fEvent->offlinetrigger = offmask;
  fEvent->onlinetrigger = onmask;
  fEvent->isCentral = isCentral;
  fEvent->isSemiCentral = isSemiCentral;
  fEvent->isMB = isMB;
  // ---

  //int icent = int(centTRK)/10;

  int centstatus = 0;
  if(centTRK<0.0||centV0M<0.0) centstatus = -1;
  if(centTRK<0.0&&centV0M<0.0) centstatus = -2;
  if(centTRK>0.0||centV0M>0.0) centstatus = 1;
  if(centTRK>0.0&&centV0M>0.0) centstatus = 2;
  if(centTRK==0.0&&centV0M==0.0) centstatus = 0;
  if(centTRK==100||centV0M==100) centstatus = -3;
  if(centTRK==100&&centV0M==100) centstatus = -4;

  if(debug>0) cout<<"centTRK "<<centTRK<<endl;
  if(debug>0) cout<<"centV0M "<<centV0M<<endl;
  fHistCentTRK->Fill(centTRK);
  fHistCentV0M->Fill(centV0M);
  // if(fabs(centTRK-centV0M)>centcut)
  //   {
  //     if(debug>0) cout<<"centrality difference outside cut, rejecting event"<<endl;
  //     return;
  //   }
  if(centstatus<2)
    {
      if(debug>0) cout<<"bad cent status, rejecting"<<endl;
      return;
    }

  if(isPhysicsEvent&&(isSemiCentral||isMB))
    {
      if(debug>1) cout<<"trigger passed"<<endl;
      fHistCentTRKkSel->Fill(centTRK);
      fHistCentV0MkSel->Fill(centV0M);
    }
  else
    {
      if(debug>0) cout<<"wrong trigger, rejecting event"<<endl;
      return;
    }

  // AOD vertex objects
  AliAODVertex *fVTX = fAOD->GetPrimaryVertex();
  AliAODVertex *fVTXSPD = fAOD->GetPrimaryVertexSPD();
  if(!fVTX&&!fVTXSPD)
    {
      if(debug>-1) cout<<"ERROR: Vertex object not available. Discarding event..."<<endl;
      return;
    }
  float zvtx = fVTX->GetZ();
  float zvtxSPD = fVTXSPD->GetZ();
  if(debug>0) cout<<"zvtx is "<<zvtx<<endl;
  if(debug>0) cout<<"zvtxSPD is "<<zvtxSPD<<endl;
  if(fabs(zvtx)>zvtxcut)
    {
      if(debug>0) cout<<"vertex outside cut, rejecting event"<<endl;
      return;
    }
  if(centstatus==2)
    {
      fHistZVtx->Fill(zvtx);
      fHistZVtxD->Fill(zvtx-zvtxSPD);
    }
  float eventX = fVTX->GetX();
  float eventY = fVTX->GetY();
  float eventZ = fVTX->GetZ();



  int f_ntrk = fAOD->GetNumberOfTracks();
  int f_nccl = fAOD->GetNumberOfCaloClusters();
  if(centstatus==-2&&f_ntrk>0) centstatus = -3;
  if(debug>0) cout<<"There are "<<f_ntrk<<" tracks in this event"<<endl;
  if(debug>0) cout<<"There are "<<f_nccl<<" calorimeter clusters in this event"<<endl;
  if(debug>0) cout<<"Centrality diagnostic is "<<centstatus<<endl;




  // ---
  fEvent->centV0M = centV0M;
  fEvent->centTRK = centTRK;
  fEvent->zvtx = zvtx;
  // ---


  // get V0 object
  AliAODVZERO *fV0 = fAOD->GetVZEROData();
  for(int i=0; i<5; i++)
    {
      float phiV0 = pi/4.0*(0.5+i%8);
      float multV0 = fV0->GetMultiplicity(i);
      fEvent->multV0[i] = multV0;
      //cout<<"i is "<<i<<" and phiV0 is "<<phiV0<<" and multV0 is "<<multV0<<endl;
    }

  AliAODZDC *fZDC = fAOD->GetZDCData();
  for(int i=0; i<64; i++)
    {
      fEvent->towerZNA[i] = (float)fZDC->GetZNATowerEnergy()[i];
      fEvent->towerZNC[i] = (float)fZDC->GetZNCTowerEnergy()[i];
      fEvent->towerZPA[i] = (float)fZDC->GetZPATowerEnergy()[i];
      fEvent->towerZPC[i] = (float)fZDC->GetZPCTowerEnergy()[i];
    }




  int runnumber = fAOD->GetRunNumber();
  float mag = fAOD->GetMagneticField();

  if(debug>0)
    {
      cout<<"runnumber is "<<runnumber<<endl;
      cout<<"magnetic field is "<<mag<<endl;
    }

  fEvent->runn = runnumber;
  fEvent->mag = mag;


  // get pid
  AliPIDResponse *fPIDResponse = handler->GetPIDResponse();
  if(!fPIDResponse)    // use PID only if no MC 
    {
      if(debug>-1) cout<<"ERROR: PIDResponse object not available. Discarding event..."<<endl;
      return;
    }



  // --- DANGEROUS TESTING!!!
  //fbit = 129; // fine!
  //fbit = 129|768; // problems!
  //fbit = 128|768; // problems!
  //fbit = 769; // fine!
  // ---

  // ------------------------------- //
  // --- Now looping over tracks --- //
  // ------------------------------- //
  // --- track loop for mapping matrix
  if(trackMap) delete trackMap;
  if(hybridMap) delete hybridMap;
  trackMap = new TExMap();
  hybridMap = new TExMap();
  for(int itrk=0; itrk<f_ntrk; itrk++)
    {
      AliAODTrack *track = fAOD->GetTrack(itrk);
      if(!track) continue;
      int gid = track->GetID();
      bool ishyb = track->IsHybridGlobalConstrainedGlobal();
      int filter = track->GetFilterMap();
      if((filter&fbit)==0) continue;
      if(ishyb) hybridMap->Add(gid,itrk);
      else trackMap->Add(gid,itrk);
    }
 
  // --- now starting main track loop
  int badbit = 0;
  int zerobit = 0;
  int dcacoverrors = 0;
  d_ntrk = 0;
  d_ntrkGBL = 0;
  d_ntrkHYB = 0;
  d_ntrkTPC = 0;
  for(int itrk = 0; itrk<f_ntrk; itrk++)
    {

      AliAODTrack *track = fAOD->GetTrack(itrk);
      if(!track)
	{
	  if(debug>0) cout<<"ERROR: Could not receive track index number "<<itrk<<endl;
	  continue;
	}

      int filter = track->GetFilterMap();

      if(filter==0) {zerobit++; continue;}

      //if(!track->TestFilterBit(fbit))
      if((filter&fbit)==0) {badbit++; continue;}

      //cout<<"sigh "<<filter<<" "<<fbit<<" "<<(filter&fbit)<<endl;

      bool ishyb = track->IsHybridGlobalConstrainedGlobal();
      bool isgbl = filter&1;
      bool istpc = filter&128;

      // ------------------------------------- //
      // --- now for PID information stuff --- //
      // ------------------------------------- //
      
      int gid = track->GetID();
      AliAODTrack *PIDtrack;
      if(gid>=0) PIDtrack = track;
      else if(ishyb) PIDtrack = fAOD->GetTrack(hybridMap->GetValue(-1-gid));
      else PIDtrack = fAOD->GetTrack(trackMap->GetValue(-1-gid));

      if(debug>10)
	{
	  cout<<"track index is "<<itrk<<endl;
	  cout<<"track ID is "<<gid<<endl;
	}

      float nsigmapionTOF = -999;
      float nsigmakaonTOF = -999;
      float nsigmaprotTOF = -999;
      float nsigmaelecTOF = -999;
      float nsigmapionTPC = -999;
      float nsigmakaonTPC = -999;
      float nsigmaprotTPC = -999;
      float nsigmaelecTPC = -999;

      if(fPIDResponse)
	{
	  nsigmapionTPC = fPIDResponse->NumberOfSigmasTPC(PIDtrack,(AliPID::EParticleType)AliPID::kPion);
	  nsigmakaonTPC = fPIDResponse->NumberOfSigmasTPC(PIDtrack,(AliPID::EParticleType)AliPID::kKaon);
	  nsigmaprotTPC = fPIDResponse->NumberOfSigmasTPC(PIDtrack,(AliPID::EParticleType)AliPID::kProton);
	  nsigmaelecTPC = fPIDResponse->NumberOfSigmasTPC(PIDtrack,(AliPID::EParticleType)AliPID::kElectron);
	  nsigmapionTOF = fPIDResponse->NumberOfSigmasTOF(PIDtrack,(AliPID::EParticleType)AliPID::kPion);
	  nsigmakaonTOF = fPIDResponse->NumberOfSigmasTOF(PIDtrack,(AliPID::EParticleType)AliPID::kKaon);
	  nsigmaprotTOF = fPIDResponse->NumberOfSigmasTOF(PIDtrack,(AliPID::EParticleType)AliPID::kProton);
	  nsigmaelecTOF = fPIDResponse->NumberOfSigmasTOF(PIDtrack,(AliPID::EParticleType)AliPID::kElectron);
	}

      // if(itrk%100==0) cout<<"TOF pid information "<<nsigmapionTOF<<" "<<nsigmakaonTOF<<" "<<nsigmaprotTOF<<" "<<nsigmaelecTOF<<" "<<endl;
      // if(itrk%100==0) cout<<"TPC pid information "<<nsigmapionTPC<<" "<<nsigmakaonTPC<<" "<<nsigmaprotTPC<<" "<<nsigmaelecTPC<<" "<<endl;

      // float nspid = 2.0; // temp...

      // bool isPion = fabs(nsigmapion) <= nspid;
      // bool isKaon = fabs(nsigmakaon) <= nspid;
      // bool isProt = fabs(nsigmaprot) <= nspid;
      // bool isElec = fabs(nsigmaelec) <= nspid;

      // bool isPionH = isPion && (!isKaon) && (!isProt);
      // bool isProtH = (!isPion) && (!isKaon) && isProt;
      // bool isPionL = isPion && (!isKaon) && (!isProt) && (!isElec);
      // bool isProtL = (!isPion) && (!isKaon) && isProt && (!isElec);

      // --- get track variables      
      float p = track->P();
      float pt = track->Pt();
      float phi = track->Phi();
      float eta = track->Eta();
      float emcalp = track->GetTrackPOnEMCal();
      float emcalpt = track->GetTrackPtOnEMCal();
      float emcalphi = track->GetTrackPhiOnEMCal();
      float emcaleta = track->GetTrackEtaOnEMCal();
      int charge = track->Charge();
      //int ncls2 = track->GetTPCncls();//same
      int ncls = track->GetTPCNcls();
      int nclsS = track->GetTPCnclsS();//often but not always zero...
      int nclsF = track->GetTPCNclsF();//findable clusters
      int ncross = track->GetTPCNCrossedRows();
      //float tpcchi2 = track->GetTPCchi2(); // ESD method only
      float chi2ndf = track->Chi2perNDF();
      //float dedxTPC = track->GetTPCsignal();//always 0...
      //float length = track->GetIntegratedLength();// always 0...

      AliAODPid *detpid = PIDtrack->GetDetPid();
      float dedxTPC = -999;
      if(detpid) dedxTPC = detpid->GetTPCsignal();
      else dedxTPC = PIDtrack->GetTPCsignal();
      float timeTOF = -999;
      if(detpid) timeTOF = detpid->GetTOFsignal();
      else timeTOF = PIDtrack->GetTOFsignal();
      float length = PIDtrack->GetIntegratedLength();// always 0...
      //if(itrk%100==0) cout<<"filtermap is "<<filter<<" and detpid is "<<detpid<<" and timeTOF is "<<timeTOF<<endl;
      //if(itrk%100==0) cout<<"filtermap is "<<filter<<" and length is "<<length<<endl;
      if(itrk%100==0) cout<<"filtermap is "<<filter<<" and chi2ndf is "<<chi2ndf<<endl;
      if(itrk%100==0) cout<<"filtermap is "<<filter<<" and ncross is "<<ncross<<endl;

      // ---

      float Tdcaxy = track->DCA();
      float Tdcaz = track->ZAtDCA();

      float dcaxy = -999;
      float dcax = -999;
      float dcay = -999;
      float dcaz = -999;

      double r[3];
      bool dcaflag = track->GetXYZ(r);
      //cout<<"fbit is "<<fbit<<" GetXYZ is "<<dcaflag<<endl;
      //printf("fbit is %d GetXYZ is %d PropagateToDCA is %d Tdcaz is %f pt is %f \n\n",fbit,dcaflag,proptodca,Tdcaz,pt);

      double DCA[2]; // dca
      double COV[3]; // covariance
      bool proptodca = track->PropagateToDCA(fVTX,mag,100.0,DCA,COV);
      if(!proptodca) {dcacoverrors++;}
      if(!proptodca&&debug>3) cout<<"No DCACOV for you!"<<endl;

      if(dcaflag)
      	{
      	  dcaxy = r[0];
      	  dcaz = r[1];
      	  if(debug>4) cout<<"GetXYZ is true, filter map is "<<filter<<endl;
      	}
      else
      	{
      	  dcax = r[0] - eventX;
      	  dcay = r[1] - eventY;
      	  dcaz = r[2] - eventZ;
      	  // --- need the sign convention for dcaxy...
      	  dcaxy = sqrt(dcax*dcax+dcay*dcay);
      	  //if((float)dcaxy!=(float)fabs((float)DCA[0])&&debug>4) cout<<"hmm... "<<dcaxy<<" "<<DCA[0]<<endl;
      	  // --- set dcaxy to value from PropagateToDCA to get correct sign
      	  dcaxy = DCA[0];
      	  // --- dcaz on the other hand is unambiguous
      	  //if(dcaz!=(float)DCA[1]&&debug>4) cout<<"hmm... "<<dcaz<<" "<<DCA[1]<<endl;
      	  if(debug>4) cout<<"GetXYZ is false, filter map is "<<filter<<endl;
      	}

      if(debug>5)
      	{
      	  cout<<"r[0] is "<<r[0]<<" ";
      	  cout<<"r[1] is "<<r[1]<<" ";
      	  cout<<"r[2] is "<<r[2]<<endl;
      	  cout<<"eventX is "<<eventX<<" ";
      	  cout<<"eventY is "<<eventY<<" ";
      	  cout<<"eventZ is "<<eventZ<<endl;
      	  cout<<"Tdcaxy is "<<Tdcaxy<<" and dcaxy is "<<dcaxy<<" and DCACOV xy is "<<DCA[0]<<endl;
      	  cout<<"Tdcaz is "<<Tdcaz<<" and dcaz is "<<dcaz<<" and DCACOV z is "<<DCA[1]<<endl;
      	}

      if((filter==128||filter==272)&&!dcaflag)
      	{
      	  dcaxy = Tdcaxy;
      	  dcaz = Tdcaz;
      	  if(debug>0)
      	    {
      	      cout<<"GetXYZ false but should be true, flipping values"<<endl;
      	      cout<<"Tdcaxy is "<<Tdcaxy<<" and dcaxy is "<<dcaxy<<" and DCACOV xy is "<<DCA[0]<<endl;
      	      cout<<"Tdcaz is "<<Tdcaz<<" and dcaz is "<<dcaz<<" and DCACOV z is "<<DCA[1]<<endl;
      	    }
      	}

      // ---

      // cout<<"Ncls "<<ncls<<endl
      // 	  <<"ncls "<<ncls2<<endl
      // 	  <<"nclsS "<<nclsS<<endl
      // 	  <<"nclsF "<<nclsF<<endl;
      // cout<<endl;


      // if(itrk%100==0)
      // 	{
      // 	  printf("filter is %d isHybrid %d \n",filter,ishyb);
      // 	}

      if(itrk%100==0&&ishyb)
	{
	  printf("Hybrid Track!  filter map is %d , map&256 is %d, map&512 is %d, map&1024 is %d, map&2048 is %d \n",
		 filter,filter&256,filter&512,filter&1024,filter&2048);
	}



      // --- some diagnostic histograms for tracks
      fHistPt->Fill(pt);
      fHistPhi->Fill(phi);
      fHistEta->Fill(eta);
      fHistCharge->Fill(charge);
      fHistTPCncls->Fill(ncls);
      fHistDedxTPC->Fill(dedxTPC);
      fHistDCAxy->Fill(dcaxy);
      fHistDCAz->Fill(dcaz);

      //Track *fTrack = new((*fTrackArray)[d_ntrk]) Track();

      if(isgbl) // global track
	{
	  Track *fTrackGlobal = new((*fTrackArrayGlobal)[d_ntrkGBL]) Track();
	  
	  fTrackGlobal->filter = filter;
	  fTrackGlobal->gid = gid;
	  fTrackGlobal->charge = charge;
	  fTrackGlobal->p = p;
	  fTrackGlobal->pt = pt;
	  fTrackGlobal->phi = phi;
	  fTrackGlobal->eta = eta;
	  fTrackGlobal->ncls = ncls;
	  fTrackGlobal->nclsS = nclsS;
	  fTrackGlobal->nclsF = nclsF;
	  fTrackGlobal->ncross = ncross;
	  fTrackGlobal->chi2ndf = chi2ndf;
	  fTrackGlobal->dcaxy = dcaxy;
	  fTrackGlobal->dcaz = dcaz;
	  fTrackGlobal->dedx = dedxTPC;
	  fTrackGlobal->ttof = timeTOF;
	  fTrackGlobal->length = length;
	  fTrackGlobal->nsigmapionTPC = nsigmapionTPC;
	  fTrackGlobal->nsigmakaonTPC = nsigmakaonTPC;
	  fTrackGlobal->nsigmaprotTPC = nsigmaprotTPC;
	  fTrackGlobal->nsigmaelecTPC = nsigmaelecTPC;
	  fTrackGlobal->nsigmapionTOF = nsigmapionTOF;
	  fTrackGlobal->nsigmakaonTOF = nsigmakaonTOF;
	  fTrackGlobal->nsigmaprotTOF = nsigmaprotTOF;
	  fTrackGlobal->nsigmaelecTOF = nsigmaelecTOF;
	  d_ntrkGBL++;
	}

      if(ishyb) // hybrid track
	{
	  Track *fTrackHybrid = new((*fTrackArrayHybrid)[d_ntrkHYB]) Track();
	  
	  fTrackHybrid->filter = filter;
	  fTrackHybrid->gid = gid;
	  fTrackHybrid->charge = charge;
	  fTrackHybrid->p = p;
	  fTrackHybrid->pt = pt;
	  fTrackHybrid->phi = phi;
	  fTrackHybrid->eta = eta;
	  fTrackHybrid->ncls = ncls;
	  fTrackHybrid->nclsS = nclsS;
	  fTrackHybrid->nclsF = nclsF;
	  fTrackHybrid->ncross = ncross;
	  fTrackHybrid->chi2ndf = chi2ndf;
	  fTrackHybrid->dcaxy = dcaxy;
	  fTrackHybrid->dcaz = dcaz;
	  fTrackHybrid->dedx = dedxTPC;
	  fTrackHybrid->ttof = timeTOF;
	  fTrackHybrid->length = length;
	  fTrackHybrid->nsigmapionTPC = nsigmapionTPC;
	  fTrackHybrid->nsigmakaonTPC = nsigmakaonTPC;
	  fTrackHybrid->nsigmaprotTPC = nsigmaprotTPC;
	  fTrackHybrid->nsigmaelecTPC = nsigmaelecTPC;
	  fTrackHybrid->nsigmapionTOF = nsigmapionTOF;
	  fTrackHybrid->nsigmakaonTOF = nsigmakaonTOF;
	  fTrackHybrid->nsigmaprotTOF = nsigmaprotTOF;
	  fTrackHybrid->nsigmaelecTOF = nsigmaelecTOF;
	  d_ntrkHYB++;
	}

      if(istpc) // hybrid track
	{
	  Track *fTrackTPCnly = new((*fTrackArrayTPCnly)[d_ntrkTPC]) Track();
	  
	  fTrackTPCnly->filter = filter;
	  fTrackTPCnly->gid = gid;
	  fTrackTPCnly->charge = charge;
	  fTrackTPCnly->p = p;
	  fTrackTPCnly->pt = pt;
	  fTrackTPCnly->phi = phi;
	  fTrackTPCnly->eta = eta;
	  fTrackTPCnly->ncls = ncls;
	  fTrackTPCnly->nclsS = nclsS;
	  fTrackTPCnly->nclsF = nclsF;
	  fTrackTPCnly->ncross = ncross;
	  fTrackTPCnly->chi2ndf = chi2ndf;
	  fTrackTPCnly->dcaxy = dcaxy;
	  fTrackTPCnly->dcaz = dcaz;
	  fTrackTPCnly->dedx = dedxTPC;
	  fTrackTPCnly->ttof = timeTOF;
	  fTrackTPCnly->length = length;
	  fTrackTPCnly->nsigmapionTPC = nsigmapionTPC;
	  fTrackTPCnly->nsigmakaonTPC = nsigmakaonTPC;
	  fTrackTPCnly->nsigmaprotTPC = nsigmaprotTPC;
	  fTrackTPCnly->nsigmaelecTPC = nsigmaelecTPC;
	  fTrackTPCnly->nsigmapionTOF = nsigmapionTOF;
	  fTrackTPCnly->nsigmakaonTOF = nsigmakaonTOF;
	  fTrackTPCnly->nsigmaprotTOF = nsigmaprotTOF;
	  fTrackTPCnly->nsigmaelecTOF = nsigmaelecTOF;
	  d_ntrkTPC++;
	}



      d_ntrk++;

      // ------------------------------------ //
      // --- that's it for the track loop --- //
      // ------------------------------------ //

    } // end track loop 

  fEvent->ntrk_Global = d_ntrkGBL;
  fEvent->ntrk_Hybrid = d_ntrkHYB;
  fEvent->ntrk_TPCnly = d_ntrkTPC;

  
  fTree->Fill();
  fTrackArrayGlobal->Clear();
  fTrackArrayHybrid->Clear();
  fTrackArrayTPCnly->Clear();

  if(debug>0)
    {
      cout<<"selected filter bit "<<fbit<<endl;
      cout<<"number of tracks with zero filter bit "<<zerobit<<endl;
      cout<<"number of tracks with wrong filter bit "<<badbit<<endl;
      cout<<"difference = ntrk - nbad = "<<f_ntrk-badbit<<endl;
      cout<<"number of tracks counted = "<<d_ntrk<<endl;
      cout<<"number of dcacov errors "<<dcacoverrors<<endl;
    }
  float fuckyou = float(dcacoverrors)/float(d_ntrk);
  fHistDCACOVerrors->Fill(fuckyou);

  


  
  
  
  // ------------------------------------ //
  // --- send data to the output list --- //
  // ------------------------------------ //

  // PostData(1,fOutputList);
  // PostData(2,fTree);

  // ------------------------- //
  // --- end of event loop --- //
  // ------------------------- //

}


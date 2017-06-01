// Author: Ron Belmont
// Date: 2009-07-28
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>

#include <sys/time.h>
 
#include "tree.h" // header for reading in tree
//#include "TaskData.h" // event and track classes for regenerating tree
 
#include "TROOT.h"
#include "TFile.h" 
#include "TTree.h"
#include "TH1.h" 
#include "TH2.h"   
#include "TProfile.h"   
//#include "TClonesArray.h"
//#include "TObject.h"



using namespace std;



int balking;
int d_ntrk;
int d_ntrkGBL;
int d_ntrkHYB;
int d_ntrkTPC;

// TTree *fTree;//!
// Event *fEvent;//!
// //TClonesArray *fTrackArray;//!
// TClonesArray *fTrackArrayGlobal;//!
// TClonesArray *fTrackArrayHybrid;//!
// TClonesArray *fTrackArrayTPCnly;//!






//ClassImp(Event); // import class inheriting from TObject
//ClassImp(Track); // import class inheriting from TObject
//ClassImp(AliAnalysisTaskData); // import class inheriting from TObject


//const float pi = 3.141592653589793;



Long64_t nevents = 0;
Long64_t ntracks = 0;
Long64_t ngoodevents = 0;
Long64_t ngoodtracks = 0;



// Main part of program
int main(int argc, char *argv[]) 
{ 

  cout<<"begin main "<<endl;

  //Char_t inFile[100];
  //Char_t outFile[100];
  char inFile[200];
  char outFile[200];
  int nevcut = 0;
  bool diagnostic = false;
  bool verbose = false;

  if(argc==1)
    {
      cout<<"Now beginning program"<<endl;
      cout<<"Program name is "<<argv[0]<<endl;
      cout<<"Please enter input file name"<<endl;
      cin>>inFile;
      cout<<"Input file is "<<inFile<<endl;
      cout<<"Please enter output file name"<<endl;
      cin>>outFile;
      cout<<"Output file is "<<outFile<<endl;
    }
  else if(argc==3)
    {
      strcpy(inFile,argv[1]);
      strcpy(outFile,argv[2]);
      cout<<"Now beginning program"<<endl;
      cout<<"Program name is "<<argv[0]<<endl;
      cout<<"Input file is "<<inFile<<endl;
      cout<<"Output file is "<<outFile<<endl;
    }
  else if(argc==4)
    {
      strcpy(inFile,argv[1]);
      strcpy(outFile,argv[2]);
      nevcut = atoi(argv[3]);
      diagnostic = true;
      if(nevcut<11) verbose = true;
      cout<<"Now beginning program with diagnostics"<<endl;
      cout<<"Program name is "<<argv[0]<<endl;
      cout<<"Input file is "<<inFile<<endl;
      cout<<"Output file is "<<outFile<<endl;
      cout<<"Number of events before termination is "<<nevcut<<endl;
    }
  else
    {
      cout<<"Wrong number of input arguments"<<endl;
      cout<<"This program takes 0 or 2 arguments"<<endl;
      cout<<"With 0 arguments it prompts the user for the file list and output root file"<<endl;
      cout<<"With 2 arguments the first is the file list and the second is the output root file"<<endl;
      return 1;
    }

  // ----------------------------

  struct timeval Time;

  gettimeofday(&Time,0);
  int begintime = Time.tv_sec;
  //cout<<"begintime is "<<begintime<<endl;

  // ----------------------------

  TFile *mData = new TFile(outFile,"recreate"); // declare output file

  // ---------------------------------------------------


  // cout<<"Now preparing event and track for tree"<<endl;

  // fEvent = new Event();
  // fTrackArrayGlobal = new TClonesArray("Track",3000);
  // fTrackArrayHybrid = new TClonesArray("Track",3000);
  // fTrackArrayTPCnly = new TClonesArray("Track",3000);

  // cout<<"Now preparing tree"<<endl;

  // fTree = new TTree("tree","tree");
  // fTree->Branch("fEvent","Event",&fEvent);
  // fTree->Branch("fTrackGlobal","TClonesArray",&fTrackArrayGlobal);
  // fTree->Branch("fTrackHybrid","TClonesArray",&fTrackArrayHybrid);
  // fTree->Branch("fTrackTPCnly","TClonesArray",&fTrackArrayTPCnly);
  // // default max size is 1.9 GB
  // //fTree->SetMaxTreeSize(1000000000);//1GB
  // fTree->SetMaxTreeSize(900000000);//500MB
  // //fTree->SetMaxTreeSize(500000000);//500MB

  // --- Now read in the pDSTs listed in the input files


  // --- Now read in the pDSTs listed in the input files

  //int ifile=0; 
  //char filename[100];
  ////char token0[100];
  ////char *token1;
  ////char *token2;
  //ifstream fin(inFile);
  //if(!fin)
  //  {
  //    cout<<"list input error: file does not exist "<<endl;
  //    return 1;
  //  }

  TH1F *th1f_p = new TH1F("th1f_p","p distribution",50,0.0,5.0);
  TH1F *th1f_pt = new TH1F("th1f_pt","p_{T} distribution",50,0.0,5.0);
  TH1F *th1f_phi = new TH1F("th1f_phi","#phi distribution",630,0,6.3);
  TH1F *th1f_eta = new TH1F("th1f_eta","#eta distribution",200,-1.0,1.0);

  TH1F *th1f_dcaz = new TH1F("th1f_dcaz","DCA_{z} distribution",100,-5.0,5.0);
  TH1F *th1f_dcaxy = new TH1F("th1f_dcaxy","DCA_{xy} distribution",100,-5.0,5.0);

  TH1F *th1f_ncls = new TH1F("th1f_ncls","TPC ncls distribution",160,0,160);
  TH1F *th1f_chi2 = new TH1F("th1f_chi2","chi2/ndf distribution",100,0,10.0);

  TH2F *th2f_pdedx_lowpid = new TH2F("th2f_pdedx_lowpid","",150,0,1.5,2005,-5,2000);
  TH2F *th2f_pdedx = new TH2F("th2f_pdedx","",500,0,5,705,-5,700);

  TH2F *th2f_psigpitpc = new TH2F("th2f_psigpitpc","",50,0,5,200,-10,10);

  TFile *f = TFile::Open(inFile);
  if(!f)
    {
      cout<<"input error: file does not exist "<<endl;
      return -1;
    }
  
  TTree *t=(TTree *)f->Get("tree");   
  if(!t)
    {
      cout<<"input error: cannot find tree "<<endl;
      return -1; 
    }

  int n=(int)t->GetEntries(); // number of events in tree
  tree *ktree = new tree(t); // pointer to tree
  for(int i=0;i<n;i++)
    { // loop over events
      
      
      ktree->GetEntry(i); 
      
      //int run = ktree->run;
      
      // stringstream ss;
      // ss<<run;
      // int runindex = myMap[ss.str()]; 
      
      
      float zvtx = ktree->zvtx;
      //fEvent->zvtx = zvtx; // fun;
      //cout<<"zvtx is "<<ktree->zvtx<<endl;

      int offlinetrigger = ktree->offlinetrigger;
      int onlinetrigger = ktree->onlinetrigger;
      bool isCentral = ktree->isCentral;
      bool isSemiCentral = ktree->isSemiCentral;
      bool isMB = ktree->isMB;
      float centV0M = ktree->centV0M;
      float centTRK = ktree->centTRK;

      float multV0[64];
      for(int i=0; i<64; i++)
	{
	  multV0[i] = ktree->multV0[i];
	}
      
      float towerZNA[5]; // ZDC energy, neutron, A side
      float towerZNC[5]; // ZDC energy, neutron, C side
      float towerZPA[5]; // ZDC energy, proton, A side
      float towerZPC[5]; // ZDC energy, proton, C side
      for(int i=0; i<5; i++)
	{
	  towerZNA[i] = ktree->towerZNA[i];
	  towerZNC[i] = ktree->towerZNC[i];
	  towerZPA[i] = ktree->towerZPA[i];
	  towerZPC[i] = ktree->towerZPC[i];
	}
      int runn = ktree->runn; // run number (e.g. 139510)
      float mag = ktree->mag; // magnetic field
      

      // d_ntrkGBL = 0;
      // d_ntrkHYB = 0;
      // d_ntrkTPC = 0;

      int ntrkGBL_max = ktree->ntrk_Global; // total number of tracks in this event for global type
      int ntrkHYB_max = ktree->ntrk_Hybrid; // total number of tracks in this event for Hybrid type
      int ntrkTPC_max = ktree->ntrk_TPCnly; // total number of tracks in this event for TPC only type 
      // fEvent->ntrk_Global = ntrkGBL_max;
      // fEvent->ntrk_Hybrid = ntrkHYB_max;
      // fEvent->ntrk_TPCnly = ntrkTPC_max;
      

      for(int itrk=0; itrk<ntrkTPC_max; itrk++)
	{
	  ntracks++; // count total number of tracks

	  // temp definitions, better ones to come later
	  bool ishyb = itrk<ntrkHYB_max;
	  bool isgbl = itrk<ntrkGBL_max;
	  bool istpc = itrk<ntrkTPC_max;

	  // temporary hackish workaround
	  //if(ktree->fTrackGlobal_p[itrk]==0) break;
	  //if(ktree->fTrackHybrid_p[itrk]==0) ishyb = false;


	  int   tpc_filter = ktree->fTrackTPCnly_filter[itrk];
	  int   tpc_gid = ktree->fTrackTPCnly_gid[itrk];
	  int   tpc_charge = ktree->fTrackTPCnly_charge[itrk];
	  float tpc_tpcmom = ktree->fTrackTPCnly_tpcmom[itrk];
	  float tpc_p = ktree->fTrackTPCnly_p[itrk];
	  float tpc_pt = ktree->fTrackTPCnly_pt[itrk];
	  float tpc_phi = ktree->fTrackTPCnly_phi[itrk];
	  float tpc_eta = ktree->fTrackTPCnly_eta[itrk];
	  int   tpc_ncls = ktree->fTrackTPCnly_ncls[itrk];
	  int   tpc_nclsS = ktree->fTrackTPCnly_nclsS[itrk];
	  int   tpc_nclsF = ktree->fTrackTPCnly_nclsF[itrk];
	  int   tpc_ncross = ktree->fTrackTPCnly_ncross[itrk];
	  float tpc_chi2ndf = ktree->fTrackTPCnly_chi2ndf[itrk];
	  float tpc_dcaxy = ktree->fTrackTPCnly_dcaxy[itrk];
	  float tpc_dcaz = ktree->fTrackTPCnly_dcaz[itrk];
	  float tpc_dedx = ktree->fTrackTPCnly_dedx[itrk];
	  float tpc_ttof = ktree->fTrackTPCnly_ttof[itrk];
	  float tpc_length = ktree->fTrackTPCnly_length[itrk];
	  float tpc_nsigmapionTPC = ktree->fTrackTPCnly_nsigmapionTPC[itrk];
	  float tpc_nsigmakaonTPC = ktree->fTrackTPCnly_nsigmakaonTPC[itrk];
	  float tpc_nsigmaprotTPC = ktree->fTrackTPCnly_nsigmaprotTPC[itrk];
	  float tpc_nsigmaelecTPC = ktree->fTrackTPCnly_nsigmaelecTPC[itrk];
	  float tpc_nsigmapionTOF = ktree->fTrackTPCnly_nsigmapionTOF[itrk];
	  float tpc_nsigmakaonTOF = ktree->fTrackTPCnly_nsigmakaonTOF[itrk];
	  float tpc_nsigmaprotTOF = ktree->fTrackTPCnly_nsigmaprotTOF[itrk];
	  float tpc_nsigmaelecTOF = ktree->fTrackTPCnly_nsigmaelecTOF[itrk];

	  th1f_p->Fill(tpc_p); // momentum
	  th1f_pt->Fill(tpc_pt); // pt
	  th1f_phi->Fill(tpc_phi); // azimuth
	  th1f_eta->Fill(tpc_eta); // pseudorapidity

	  th1f_dcaz->Fill(tpc_dcaz); // longitudinal DCA
	  th1f_dcaxy->Fill(tpc_dcaxy); // transverse DCA

	  th1f_ncls->Fill(tpc_ncls); // number of TPC clusters (number of hits)
	  th1f_chi2->Fill(tpc_chi2ndf);	// chi2/ndf for tracks in TPC





	  int   gbl_filter = ktree->fTrackGlobal_filter[itrk];
	  int   gbl_gid = ktree->fTrackGlobal_gid[itrk];
	  int   gbl_charge = ktree->fTrackGlobal_charge[itrk];
	  float gbl_tpcmom = ktree->fTrackGlobal_tpcmom[itrk];
	  float gbl_p = ktree->fTrackGlobal_p[itrk];
	  float gbl_pt = ktree->fTrackGlobal_pt[itrk];
	  float gbl_phi = ktree->fTrackGlobal_phi[itrk];
	  float gbl_eta = ktree->fTrackGlobal_eta[itrk];
	  int   gbl_ncls = ktree->fTrackGlobal_ncls[itrk];
	  int   gbl_nclsS = ktree->fTrackGlobal_nclsS[itrk];
	  int   gbl_nclsF = ktree->fTrackGlobal_nclsF[itrk];
	  int   gbl_ncross = ktree->fTrackGlobal_ncross[itrk];
	  float gbl_chi2ndf = ktree->fTrackGlobal_chi2ndf[itrk];
	  float gbl_dcaxy = ktree->fTrackGlobal_dcaxy[itrk];
	  float gbl_dcaz = ktree->fTrackGlobal_dcaz[itrk];
	  float gbl_dedx = ktree->fTrackGlobal_dedx[itrk];
	  float gbl_ttof = ktree->fTrackGlobal_ttof[itrk];
	  float gbl_length = ktree->fTrackGlobal_length[itrk];
	  float gbl_nsigmapionTPC = ktree->fTrackGlobal_nsigmapionTPC[itrk];
	  float gbl_nsigmakaonTPC = ktree->fTrackGlobal_nsigmakaonTPC[itrk];
	  float gbl_nsigmaprotTPC = ktree->fTrackGlobal_nsigmaprotTPC[itrk];
	  float gbl_nsigmaelecTPC = ktree->fTrackGlobal_nsigmaelecTPC[itrk];
	  float gbl_nsigmapionTOF = ktree->fTrackGlobal_nsigmapionTOF[itrk];
	  float gbl_nsigmakaonTOF = ktree->fTrackGlobal_nsigmakaonTOF[itrk];
	  float gbl_nsigmaprotTOF = ktree->fTrackGlobal_nsigmaprotTOF[itrk];
	  float gbl_nsigmaelecTOF = ktree->fTrackGlobal_nsigmaelecTOF[itrk];

	  if(itrk>=ntrkHYB_max) continue;

	  int   hyb_filter = ktree->fTrackHybrid_filter[itrk];
	  int   hyb_gid = ktree->fTrackHybrid_gid[itrk];
	  int   hyb_charge = ktree->fTrackHybrid_charge[itrk];
	  float hyb_tpcmom = ktree->fTrackHybrid_tpcmom[itrk];
	  float hyb_p = ktree->fTrackHybrid_p[itrk];
	  float hyb_pt = ktree->fTrackHybrid_pt[itrk];
	  float hyb_phi = ktree->fTrackHybrid_phi[itrk];
	  float hyb_eta = ktree->fTrackHybrid_eta[itrk];
	  int   hyb_ncls = ktree->fTrackHybrid_ncls[itrk];
	  int   hyb_nclsS = ktree->fTrackHybrid_nclsS[itrk];
	  int   hyb_nclsF = ktree->fTrackHybrid_nclsF[itrk];
	  int   hyb_ncross = ktree->fTrackHybrid_ncross[itrk];
	  float hyb_chi2ndf = ktree->fTrackHybrid_chi2ndf[itrk];
	  float hyb_dcaxy = ktree->fTrackHybrid_dcaxy[itrk];
	  float hyb_dcaz = ktree->fTrackHybrid_dcaz[itrk];
	  float hyb_dedx = ktree->fTrackHybrid_dedx[itrk];
	  float hyb_ttof = ktree->fTrackHybrid_ttof[itrk];
	  float hyb_length = ktree->fTrackHybrid_length[itrk];
	  float hyb_nsigmapionTPC = ktree->fTrackHybrid_nsigmapionTPC[itrk];
	  float hyb_nsigmakaonTPC = ktree->fTrackHybrid_nsigmakaonTPC[itrk];
	  float hyb_nsigmaprotTPC = ktree->fTrackHybrid_nsigmaprotTPC[itrk];
	  float hyb_nsigmaelecTPC = ktree->fTrackHybrid_nsigmaelecTPC[itrk];
	  float hyb_nsigmapionTOF = ktree->fTrackHybrid_nsigmapionTOF[itrk];
	  float hyb_nsigmakaonTOF = ktree->fTrackHybrid_nsigmakaonTOF[itrk];
	  float hyb_nsigmaprotTOF = ktree->fTrackHybrid_nsigmaprotTOF[itrk];
	  float hyb_nsigmaelecTOF = ktree->fTrackHybrid_nsigmaelecTOF[itrk];

	  // th2f_pdedx->Fill(hyb_p,hyb_dedx);
	  // th2f_psigpitpc->Fill(hyb_p,hyb_nsigmapionTPC);

	  th2f_pdedx_lowpid->Fill(tpc_tpcmom,tpc_dedx);
	  th2f_pdedx->Fill(tpc_p,tpc_dedx);
	  th2f_psigpitpc->Fill(tpc_p,tpc_nsigmapionTPC);

	  
	} // end of track loop
      

      nevents++;
      //if(nevents>10000) break;

    } // end of event loop
    

  // this could cause a lot of pain and sorrow...
  delete ktree; // ?
  //ktree->Delete(); // method doesn't exist
  
  


  
  // write the histograms to file and close
  mData->Write();  
  mData->Close();
  
  cout<<"Number of events: "<<nevents<<endl;
  cout<<"Number of tracks: "<<ntracks<<endl;
  
  gettimeofday(&Time,0);
  int endtime = Time.tv_sec;
  //cout<<"endtime is "<<endtime<<endl;
  
  int tdiff = endtime-begintime;
  
  cout<<"End of program."<<endl;
  cout<<"Execution time: "<<tdiff<<" seconds"<<endl;
  
  exit(0); 

} // end of main

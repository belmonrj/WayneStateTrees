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
#include "TaskData.h" // event and track classes for regenerating tree
 
#include "TROOT.h"
#include "TFile.h" 
#include "TTree.h"
#include "TH1.h" 
#include "TH2.h"   
#include "TProfile.h"   
#include "TClonesArray.h"
#include "TObject.h"



using namespace std;



int balking;
int d_ntrk;
int d_ntrkGBL;
int d_ntrkHYB;
int d_ntrkTPC;

TTree *fTree;//!
Event *fEvent;//!
//TClonesArray *fTrackArray;//!
TClonesArray *fTrackArrayGlobal;//!
TClonesArray *fTrackArrayHybrid;//!
TClonesArray *fTrackArrayTPCnly;//!






ClassImp(Event); // import class inheriting from TObject
ClassImp(Track); // import class inheriting from TObject
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

  //struct timeval Time;

  //gettimeofday(&Time,0);
  //int begintime = Time.tv_sec;
  //cout<<"begintime is "<<begintime<<endl;

  // ----------------------------

  TFile *mData = new TFile(outFile,"recreate"); // declare output file

  // ---------------------------------------------------


  cout<<"Now preparing event and track for tree"<<endl;

  fEvent = new Event();
  fTrackArrayGlobal = new TClonesArray("Track",3000);
  fTrackArrayHybrid = new TClonesArray("Track",3000);
  fTrackArrayTPCnly = new TClonesArray("Track",3000);

  cout<<"Now preparing tree"<<endl;

  fTree = new TTree("tree","tree");
  fTree->Branch("fEvent","Event",&fEvent);
  fTree->Branch("g","TClonesArray",&fTrackArrayGlobal);
  fTree->Branch("h","TClonesArray",&fTrackArrayHybrid);
  fTree->Branch("t","TClonesArray",&fTrackArrayTPCnly);
  // default max size is 1.9 GB
  fTree->SetMaxTreeSize(2000000000);//2GB
  //fTree->SetMaxTreeSize(1000000000);//1GB
  //fTree->SetMaxTreeSize(900000000);//500MB
  //fTree->SetMaxTreeSize(500000000);//500MB

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
      fEvent->zvtx = zvtx; // fun;
      //cout<<"zvtx is "<<ktree->zvtx<<endl;

      fEvent->offlinetrigger = ktree->offlinetrigger;
      fEvent->onlinetrigger = ktree->onlinetrigger;
      fEvent->isCentral = ktree->isCentral;
      fEvent->isSemiCentral = ktree->isSemiCentral;
      fEvent->isMB = ktree->isMB;
      fEvent->centV0M = ktree->centV0M;
      fEvent->centTRK = ktree->centTRK;

      for(int i=0; i<64; i++)
	{
	  fEvent->multV0[i] = ktree->multV0[i];
	}
      
      for(int i=0; i<5; i++)
	{
	  fEvent->towerZNA[i] = ktree->towerZNA[i];
	  fEvent->towerZNC[i] = ktree->towerZNC[i];
	  fEvent->towerZPA[i] = ktree->towerZPA[i];
	  fEvent->towerZPC[i] = ktree->towerZPC[i];
	}
      fEvent->runn = ktree->runn;
      fEvent->mag = ktree->mag;
      

      d_ntrkGBL = 0;
      d_ntrkHYB = 0;
      d_ntrkTPC = 0;

      int ntrkGBL_max = ktree->ntrk_Global;
      int ntrkHYB_max = ktree->ntrk_Hybrid;
      int ntrkTPC_max = ktree->ntrk_TPCnly;
      fEvent->ntrk_gbl = ntrkGBL_max;
      fEvent->ntrk_hyb = ntrkHYB_max;
      fEvent->ntrk_tpc = ntrkTPC_max;
      
      // another temporary thingy
      //int NTRK = 4000;
      int NTRK = ntrkGBL_max;
      if(ntrkHYB_max>NTRK) NTRK = ntrkHYB_max;
      if(ntrkTPC_max>NTRK) NTRK = ntrkTPC_max;

      for(int itrk=0; itrk<NTRK; itrk++)
	{
	  ntracks++; // count total number of tracks

	  // temp definitions, better ones to come later
	  bool ishyb = itrk<ntrkHYB_max;
	  bool isgbl = itrk<ntrkGBL_max;
	  bool istpc = itrk<ntrkTPC_max;

	  // temporary hackish workaround
	  //if(ktree->fTrackGlobal_p[itrk]==0) break;
	  //if(ktree->fTrackHybrid_p[itrk]==0) ishyb = false;


	  if(isgbl) // global track
	    {
	      Track *g = new((*fTrackArrayGlobal)[d_ntrkGBL]) Track();
	      //Track *fTrackGlobal = new((*fTrackArrayGlobal)[d_ntrkGBL]) Track::Track();
	      g->filter = ktree->fTrackGlobal_filter[itrk];
	      //cout<<"global filter is "<<ktree->fTrackGlobal_filter[itrk]<<endl;
	      //continue;
	      g->gid = ktree->fTrackGlobal_gid[itrk];
	      g->charge = ktree->fTrackGlobal_charge[itrk];
	      g->tpcmom = ktree->fTrackGlobal_tpcmom[itrk];
	      g->p = ktree->fTrackGlobal_p[itrk];
	      g->pt = ktree->fTrackGlobal_pt[itrk];
	      g->phi = ktree->fTrackGlobal_phi[itrk];
	      g->eta = ktree->fTrackGlobal_eta[itrk];
	      g->ncls = ktree->fTrackGlobal_ncls[itrk];
	      g->nclsS = ktree->fTrackGlobal_nclsS[itrk];
	      g->nclsF = ktree->fTrackGlobal_nclsF[itrk];
	      g->ncross = ktree->fTrackGlobal_ncross[itrk];
	      g->chi2pc = ktree->fTrackGlobal_chi2ndf[itrk];
	      g->dcaxy = ktree->fTrackGlobal_dcaxy[itrk];
	      g->dcaz = ktree->fTrackGlobal_dcaz[itrk];
	      g->dedx = ktree->fTrackGlobal_dedx[itrk];
	      g->ttof = ktree->fTrackGlobal_ttof[itrk];
	      g->length = ktree->fTrackGlobal_length[itrk];
	      g->nspiTPC = ktree->fTrackGlobal_nsigmapionTPC[itrk];
	      g->nskTPC = ktree->fTrackGlobal_nsigmakaonTPC[itrk];
	      g->nspTPC = ktree->fTrackGlobal_nsigmaprotTPC[itrk];
	      g->nseTPC = ktree->fTrackGlobal_nsigmaelecTPC[itrk];
	      g->nspiTOF = ktree->fTrackGlobal_nsigmapionTOF[itrk];
	      g->nskTOF = ktree->fTrackGlobal_nsigmakaonTOF[itrk];
	      g->nspTOF = ktree->fTrackGlobal_nsigmaprotTOF[itrk];
	      g->nseTOF = ktree->fTrackGlobal_nsigmaelecTOF[itrk];
	      d_ntrkGBL++;
	    }
	  
	  if(ishyb) // hybrid track
	    {
	      Track *h = new((*fTrackArrayHybrid)[d_ntrkHYB]) Track();
	      //Track *fTrackHybrid = new((*fTrackArrayHybrid)[d_ntrkHYB]) Track::Track();
	      h->filter = ktree->fTrackHybrid_filter[itrk];
	      h->gid = ktree->fTrackHybrid_gid[itrk];
	      h->charge = ktree->fTrackHybrid_charge[itrk];
	      h->tpcmom = ktree->fTrackHybrid_tpcmom[itrk];
	      h->p = ktree->fTrackHybrid_p[itrk];
	      h->pt = ktree->fTrackHybrid_pt[itrk];
	      h->phi = ktree->fTrackHybrid_phi[itrk];
	      h->eta = ktree->fTrackHybrid_eta[itrk];
	      h->ncls = ktree->fTrackHybrid_ncls[itrk];
	      h->nclsS = ktree->fTrackHybrid_nclsS[itrk];
	      h->nclsF = ktree->fTrackHybrid_nclsF[itrk];
	      h->ncross = ktree->fTrackHybrid_ncross[itrk];
	      h->chi2pc = ktree->fTrackHybrid_chi2ndf[itrk];
	      h->dcaxy = ktree->fTrackHybrid_dcaxy[itrk];
	      h->dcaz = ktree->fTrackHybrid_dcaz[itrk];
	      h->dedx = ktree->fTrackHybrid_dedx[itrk];
	      h->ttof = ktree->fTrackHybrid_ttof[itrk];
	      h->length = ktree->fTrackHybrid_length[itrk];
	      h->nspiTPC = ktree->fTrackHybrid_nsigmapionTPC[itrk];
	      h->nskTPC = ktree->fTrackHybrid_nsigmakaonTPC[itrk];
	      h->nspTPC = ktree->fTrackHybrid_nsigmaprotTPC[itrk];
	      h->nseTPC = ktree->fTrackHybrid_nsigmaelecTPC[itrk];
	      h->nspiTOF = ktree->fTrackHybrid_nsigmapionTOF[itrk];
	      h->nskTOF = ktree->fTrackHybrid_nsigmakaonTOF[itrk];
	      h->nspTOF = ktree->fTrackHybrid_nsigmaprotTOF[itrk];
	      h->nseTOF = ktree->fTrackHybrid_nsigmaelecTOF[itrk];
	      d_ntrkHYB++;
	    }
	  
	  if(istpc) // hybrid track
	    {
	      Track *t = new((*fTrackArrayTPCnly)[d_ntrkTPC]) Track();
	      //Track *fTrackTPCnly = new((*fTrackArrayTPCnly)[d_ntrkTPC]) Track::Track();
	      t->filter = ktree->fTrackTPCnly_filter[itrk];
	      t->gid = ktree->fTrackTPCnly_gid[itrk];
	      t->charge = ktree->fTrackTPCnly_charge[itrk];
	      t->tpcmom = ktree->fTrackTPCnly_tpcmom[itrk];
	      t->p = ktree->fTrackTPCnly_p[itrk];
	      t->pt = ktree->fTrackTPCnly_pt[itrk];
	      t->phi = ktree->fTrackTPCnly_phi[itrk];
	      t->eta = ktree->fTrackTPCnly_eta[itrk];
	      t->ncls = ktree->fTrackTPCnly_ncls[itrk];
	      t->nclsS = ktree->fTrackTPCnly_nclsS[itrk];
	      t->nclsF = ktree->fTrackTPCnly_nclsF[itrk];
	      t->ncross = ktree->fTrackTPCnly_ncross[itrk];
	      t->chi2pc = ktree->fTrackTPCnly_chi2ndf[itrk];
	      t->dcaxy = ktree->fTrackTPCnly_dcaxy[itrk];
	      t->dcaz = ktree->fTrackTPCnly_dcaz[itrk];
	      t->dedx = ktree->fTrackTPCnly_dedx[itrk];
	      t->ttof = ktree->fTrackTPCnly_ttof[itrk];
	      t->length = ktree->fTrackTPCnly_length[itrk];
	      t->nspiTPC = ktree->fTrackTPCnly_nsigmapionTPC[itrk];
	      t->nskTPC = ktree->fTrackTPCnly_nsigmakaonTPC[itrk];
	      t->nspTPC = ktree->fTrackTPCnly_nsigmaprotTPC[itrk];
	      t->nseTPC = ktree->fTrackTPCnly_nsigmaelecTPC[itrk];
	      t->nspiTOF = ktree->fTrackTPCnly_nsigmapionTOF[itrk];
	      t->nskTOF = ktree->fTrackTPCnly_nsigmakaonTOF[itrk];
	      t->nspTOF = ktree->fTrackTPCnly_nsigmaprotTOF[itrk];
	      t->nseTOF = ktree->fTrackTPCnly_nsigmaelecTOF[itrk];
	      d_ntrkTPC++;
	    }
	  
	  
	} // end of track loop
      
      fTree->Fill();
      fTrackArrayGlobal->Clear();
      fTrackArrayHybrid->Clear();
      fTrackArrayTPCnly->Clear();

      nevents++;

    } // end of event loop
    

  // this could cause a lot of pain and sorrow...
  delete ktree; // ?
  //ktree->Delete(); // method doesn't exist
  
  
  
  // write the histograms to file and close
  mData->Write();  
  mData->Close();
  
  cout<<"Number of events: "<<nevents<<endl;
  cout<<"Number of tracks: "<<ntracks<<endl;
  
  //gettimeofday(&Time,0);
  //int endtime = Time.tv_sec;
  //cout<<"endtime is "<<endtime<<endl;
  
  //int tdiff = endtime-begintime;
  
  cout<<"End of program."<<endl;
  //cout<<"Execution time: "<<tdiff<<" seconds"<<endl;
  
  exit(0); 

} // end of main

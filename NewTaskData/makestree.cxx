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
 
#include "tree.h"
 
#include "TROOT.h"
#include "TFile.h" 
#include "TTree.h"
#include "TH1.h" 
#include "TH2.h"   
#include "TProfile.h"   
//#include "TRandom3.h"

using namespace std;



const float phbeta  = 29.9792458;
const float mpion   = 0.13957;
const float mkaon   = 0.493677;
const float mproton = 0.938270;
const float pi = 3.141592653589793;



Long64_t nevents = 0;
Long64_t ntracks = 0;
Long64_t ngoodevents = 0;
Long64_t ngoodtracks = 0;



// Main part of program
int main(int argc, char *argv[]) 
{ 

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

  // -------------------------- //
  // --- Declare histograms --- //
  // -------------------------- //
  
  TH1F *hhcent = new TH1F("hhcent","cent",100,0,100);
  TH1F *hhcend = new TH1F("hhcend","cend",100,0,100);
  TH1F *hhcenT = new TH1F("hhcenT","cenT",100,0,100);
  TH1F *hhciff = new TH1F("hhciff","cent diff",100,-50,50);
  TH1F *hhzvtx = new TH1F("hhzvtx","zvtx",100,-50,50);

  TH1F *hhpt = new TH1F("hhpt","pt",100,0,10);
  TH1F *hhmom = new TH1F("hhmom","momentum",100,0,10);
  TH1F *hhdcaz = new TH1F("hhdcaz","dcaz",200,-1,1);
  TH1F *hhdcaxy = new TH1F("hhdcaxy","dcaxy",200,-1,1);

  TH1F *hqadLR = new TH1F("hqadLR","hqadLR",100,-1,1);
  TH1F *hqadPT = new TH1F("hqadPT","hqadPT",100,-1,1);
  TH1F *hqad12 = new TH1F("hqad12","hqad12",100,-1,1);

  TH2F *hhqadLR = new TH2F("hhqadLR","hhqadLR",100,-0.2,0.2,100,-0.2,0.2);
  TH2F *hhqadPT = new TH2F("hhqadPT","hhqadPT",100,-0.2,0.2,100,-0.2,0.2);
  TH2F *hhqad12 = new TH2F("hhqad12","hhqad12",100,-0.2,0.2,100,-0.2,0.2);


  TTree *stree = new TTree("shorttree","shorttree");
  const int maxn = 8000;
  const int hmax = 9;
  int   d_ntrk;
  float d_cent;
  float d_cend;
  float d_cenT;
  float d_zvtx;
  float d_runn;
  int   d_hmax = hmax;
  float d_qasymmX;
  float d_qasymLX;
  float d_qasymRX;
  float d_qasymEX;
  float d_qasymm;
  float d_qasymL;
  float d_qasymR;
  float d_qasymC;
  float d_qasymE;
  float d_qasymP;
  float d_qasymT;
  float d_qasymA1;
  float d_qasymA2;
  //new...
  float d_ntrkm;
  float d_ntrkL;
  float d_ntrkR;
  float d_ntrkC;
  float d_ntrkE;
  float d_ntrkP;
  float d_ntrkT;
  float d_ntrkA1;
  float d_ntrkA2;
  float d_ntrkposm;
  float d_ntrkposL;
  float d_ntrkposR;
  float d_ntrkposC;
  float d_ntrkposE;
  float d_ntrkposP;
  float d_ntrkposT;
  float d_ntrkposA1;
  float d_ntrkposA2;
  float d_ntrknegm;
  float d_ntrknegL;
  float d_ntrknegR;
  float d_ntrknegC;
  float d_ntrknegE;
  float d_ntrknegP;
  float d_ntrknegT;
  float d_ntrknegA1;
  float d_ntrknegA2;


  float d_Xpl[hmax];
  float d_Ypl[hmax];
  float d_Xpr[hmax];
  float d_Ypr[hmax];
  float d_Xnl[hmax];
  float d_Ynl[hmax];
  float d_Xnr[hmax];
  float d_Ynr[hmax];

  float d_Xpll[hmax];
  float d_Ypll[hmax];
  float d_Xprr[hmax];
  float d_Yprr[hmax];
  float d_Xnll[hmax];
  float d_Ynll[hmax];
  float d_Xnrr[hmax];
  float d_Ynrr[hmax];

  float d_Xa[hmax];
  float d_Ya[hmax];
  float d_Xc[hmax];
  float d_Yc[hmax];

  float d_wXpl[hmax];
  float d_wYpl[hmax];
  float d_wXpr[hmax];
  float d_wYpr[hmax];
  float d_wXnl[hmax];
  float d_wYnl[hmax];
  float d_wXnr[hmax];
  float d_wYnr[hmax];

  float d_wXpll[hmax];
  float d_wYpll[hmax];
  float d_wXprr[hmax];
  float d_wYprr[hmax];
  float d_wXnll[hmax];
  float d_wYnll[hmax];
  float d_wXnrr[hmax];
  float d_wYnrr[hmax];

  // new

  float d_tXpl[hmax];
  float d_tYpl[hmax];
  float d_tXpr[hmax];
  float d_tYpr[hmax];
  float d_tXnl[hmax];
  float d_tYnl[hmax];
  float d_tXnr[hmax];
  float d_tYnr[hmax];

  float d_tXpll[hmax];
  float d_tYpll[hmax];
  float d_tXprr[hmax];
  float d_tYprr[hmax];
  float d_tXnll[hmax];
  float d_tYnll[hmax];
  float d_tXnrr[hmax];
  float d_tYnrr[hmax];

  //

  // COME BACK HERE

  float d_a1Xp[hmax];
  float d_a1Yp[hmax];
  float d_a1Xn[hmax];
  float d_a1Yn[hmax];
  float d_a2Xp[hmax];
  float d_a2Yp[hmax];
  float d_a2Xn[hmax];
  float d_a2Yn[hmax];

  float d_qXp[hmax];
  float d_qYp[hmax];
  float d_qXn[hmax];
  float d_qYn[hmax];

  // end new

  float d_psia[hmax];
  float d_psic[hmax];
  float d_psir[hmax];
  float d_psil[hmax];
  float d_psip[hmax];
  float d_psin[hmax];
  
  float d_mom[maxn];
  float d_pt[maxn];
  float d_eta[maxn];
  float d_phi[maxn];
  float d_charge[maxn];

  float d_q22ev;
  float d_q22Pev;
  float d_q22Nev;
  float d_q22gap0ev;
  float d_q22gap0Pev;
  float d_q22gap0Nev;
  float d_q22gap1ev;
  float d_q22gap1Pev;
  float d_q22gap1Nev;

  stree->Branch("ntrk",&d_ntrk,"ntrk/I");
  stree->Branch("cent",&d_cent,"cent/F");
  stree->Branch("cend",&d_cend,"cend/F");
  stree->Branch("cenT",&d_cenT,"cenT/F");
  stree->Branch("zvtx",&d_zvtx,"zvtx/F");
  stree->Branch("runn",&d_runn,"runn/F");
  stree->Branch("hmax",&d_hmax,"hmax/I");
  stree->Branch("qasymmX",&d_qasymmX,"qasymmX/F");
  stree->Branch("qasymLX",&d_qasymLX,"qasymLX/F");
  stree->Branch("qasymRX",&d_qasymRX,"qasymRX/F");
  stree->Branch("qasymEX",&d_qasymEX,"qasymEX/F");
  stree->Branch("qasymm",&d_qasymm,"qasymm/F");
  stree->Branch("qasymL",&d_qasymL,"qasymL/F");
  stree->Branch("qasymR",&d_qasymR,"qasymR/F");
  stree->Branch("qasymC",&d_qasymC,"qasymC/F");
  stree->Branch("qasymE",&d_qasymE,"qasymE/F");
  stree->Branch("qasymP",&d_qasymP,"qasymP/F");
  stree->Branch("qasymT",&d_qasymT,"qasymT/F");
  stree->Branch("qasymA1",&d_qasymA1,"qasymA1/F");
  stree->Branch("qasymA2",&d_qasymA2,"qasymA2/F");
  // new...
  stree->Branch("ntrkm",&d_ntrkm,"ntrkm/F");
  stree->Branch("ntrkL",&d_ntrkL,"ntrkL/F");
  stree->Branch("ntrkR",&d_ntrkR,"ntrkR/F");
  stree->Branch("ntrkC",&d_ntrkC,"ntrkC/F");
  stree->Branch("ntrkE",&d_ntrkE,"ntrkE/F");
  stree->Branch("ntrkP",&d_ntrkP,"ntrkP/F");
  stree->Branch("ntrkT",&d_ntrkT,"ntrkT/F");
  stree->Branch("ntrkA1",&d_ntrkA1,"ntrkA1/F");
  stree->Branch("ntrkA2",&d_ntrkA2,"ntrkA2/F");
  stree->Branch("ntrkposm",&d_ntrkposm,"ntrkposm/F");
  stree->Branch("ntrkposL",&d_ntrkposL,"ntrkposL/F");
  stree->Branch("ntrkposR",&d_ntrkposR,"ntrkposR/F");
  stree->Branch("ntrkposC",&d_ntrkposC,"ntrkposC/F");
  stree->Branch("ntrkposE",&d_ntrkposE,"ntrkposE/F");
  stree->Branch("ntrkposT",&d_ntrkposT,"ntrkposT/F");
  stree->Branch("ntrkposA1",&d_ntrkposA1,"ntrkposA1/F");
  stree->Branch("ntrkposA2",&d_ntrkposA2,"ntrkposA2/F");
  stree->Branch("ntrknegm",&d_ntrknegm,"ntrknegm/F");
  stree->Branch("ntrknegL",&d_ntrknegL,"ntrknegL/F");
  stree->Branch("ntrknegR",&d_ntrknegR,"ntrknegR/F");
  stree->Branch("ntrknegC",&d_ntrknegC,"ntrknegC/F");
  stree->Branch("ntrknegE",&d_ntrknegE,"ntrknegE/F");
  stree->Branch("ntrknegP",&d_ntrknegP,"ntrknegP/F");
  stree->Branch("ntrknegT",&d_ntrknegT,"ntrknegT/F");
  stree->Branch("ntrknegA1",&d_ntrknegA1,"ntrknegA1/F");
  stree->Branch("ntrknegA2",&d_ntrknegA2,"ntrknegA2/F");


  stree->Branch("Xpl",d_Xpl,"Xpl[hmax]/F");
  stree->Branch("Ypl",d_Ypl,"Ypl[hmax]/F");
  stree->Branch("Xpr",d_Xpr,"Xpr[hmax]/F");
  stree->Branch("Ypr",d_Ypr,"Ypr[hmax]/F");
  stree->Branch("Xnl",d_Xnl,"Xnl[hmax]/F");
  stree->Branch("Ynl",d_Ynl,"Ynl[hmax]/F");
  stree->Branch("Xnr",d_Xnr,"Xnr[hmax]/F");
  stree->Branch("Ynr",d_Ynr,"Ynr[hmax]/F");
  stree->Branch("Xpll",d_Xpll,"Xpll[hmax]/F");
  stree->Branch("Ypll",d_Ypll,"Ypll[hmax]/F");
  stree->Branch("Xprr",d_Xprr,"Xprr[hmax]/F");
  stree->Branch("Yprr",d_Yprr,"Yprr[hmax]/F");
  stree->Branch("Xnll",d_Xnll,"Xnll[hmax]/F");
  stree->Branch("Ynll",d_Ynll,"Ynll[hmax]/F");
  stree->Branch("Xnrr",d_Xnrr,"Xnrr[hmax]/F");
  stree->Branch("Ynrr",d_Ynrr,"Ynrr[hmax]/F");
  stree->Branch("Xa",d_Xa,"Xa[hmax]/F");
  stree->Branch("Ya",d_Ya,"Ya[hmax]/F");
  stree->Branch("Xc",d_Xc,"Xc[hmax]/F");
  stree->Branch("Yc",d_Yc,"Yc[hmax]/F");
  stree->Branch("wXpl",d_wXpl,"wXpl[hmax]/F");
  stree->Branch("wYpl",d_wYpl,"wYpl[hmax]/F");
  stree->Branch("wXpr",d_wXpr,"wXpr[hmax]/F");
  stree->Branch("wYpr",d_wYpr,"wYpr[hmax]/F");
  stree->Branch("wXnl",d_wXnl,"wXnl[hmax]/F");
  stree->Branch("wYnl",d_wYnl,"wYnl[hmax]/F");
  stree->Branch("wXnr",d_wXnr,"wXnr[hmax]/F");
  stree->Branch("wYnr",d_wYnr,"wYnr[hmax]/F");
  stree->Branch("wXpll",d_wXpll,"wXpll[hmax]/F");
  stree->Branch("wYpll",d_wYpll,"wYpll[hmax]/F");
  stree->Branch("wXprr",d_wXprr,"wXprr[hmax]/F");
  stree->Branch("wYprr",d_wYprr,"wYprr[hmax]/F");
  stree->Branch("wXnll",d_wXnll,"wXnll[hmax]/F");
  stree->Branch("wYnll",d_wYnll,"wYnll[hmax]/F");
  stree->Branch("wXnrr",d_wXnrr,"wXnrr[hmax]/F");
  stree->Branch("wYnrr",d_wYnrr,"wYnrr[hmax]/F");
  // new
  stree->Branch("tXpl",d_tXpl,"tXpl[hmax]/F");
  stree->Branch("tYpl",d_tYpl,"tYpl[hmax]/F");
  stree->Branch("tXpr",d_tXpr,"tXpr[hmax]/F");
  stree->Branch("tYpr",d_tYpr,"tYpr[hmax]/F");
  stree->Branch("tXnl",d_tXnl,"tXnl[hmax]/F");
  stree->Branch("tYnl",d_tYnl,"tYnl[hmax]/F");
  stree->Branch("tXnr",d_tXnr,"tXnr[hmax]/F");
  stree->Branch("tYnr",d_tYnr,"tYnr[hmax]/F");
  stree->Branch("tXpll",d_tXpll,"tXpll[hmax]/F");
  stree->Branch("tYpll",d_tYpll,"tYpll[hmax]/F");
  stree->Branch("tXprr",d_tXprr,"tXprr[hmax]/F");
  stree->Branch("tYprr",d_tYprr,"tYprr[hmax]/F");
  stree->Branch("tXnll",d_tXnll,"tXnll[hmax]/F");
  stree->Branch("tYnll",d_tYnll,"tYnll[hmax]/F");
  stree->Branch("tXnrr",d_tXnrr,"tXnrr[hmax]/F");
  stree->Branch("tYnrr",d_tYnrr,"tYnrr[hmax]/F");
  stree->Branch("a1Xp",d_a1Xp,"a1Xp[hmax]/F");
  stree->Branch("a1Yp",d_a1Yp,"a1Yp[hmax]/F");
  stree->Branch("a2Xp",d_a2Xp,"a2Xp[hmax]/F");
  stree->Branch("a2Yp",d_a2Yp,"a2Yp[hmax]/F");
  stree->Branch("a1Xn",d_a1Xn,"a1Xn[hmax]/F");
  stree->Branch("a1Yn",d_a1Yn,"a1Yn[hmax]/F");
  stree->Branch("a2Xn",d_a2Xn,"a2Xn[hmax]/F");
  stree->Branch("a2Yn",d_a2Yn,"a2Yn[hmax]/F");
  stree->Branch("qXp",d_qXp,"qXp[hmax]/F");
  stree->Branch("qYp",d_qYp,"qYp[hmax]/F");
  stree->Branch("qXn",d_qXn,"qXn[hmax]/F");
  stree->Branch("qYn",d_qYn,"qYn[hmax]/F");
  // end new
  stree->Branch("psia",d_psia,"psia[hmax]/F");
  stree->Branch("psic",d_psic,"psic[hmax]/F");
  stree->Branch("psir",d_psir,"psir[hmax]/F");
  stree->Branch("psil",d_psil,"psil[hmax]/F");
  stree->Branch("psip",d_psip,"psip[hmax]/F");
  stree->Branch("psin",d_psin,"psin[hmax]/F");

  stree->Branch("q22ev",&d_q22ev,"q22ev/F");
  stree->Branch("q22Pev",&d_q22Pev,"q22Pev/F");
  stree->Branch("q22Nev",&d_q22Nev,"q22Nev/F");
  stree->Branch("q22gap0ev",&d_q22gap0ev,"q22gap0ev/F");
  stree->Branch("q22gap0Pev",&d_q22gap0Pev,"q22gap0Pev/F");
  stree->Branch("q22gap0Nev",&d_q22gap0Nev,"q22gap0Nev/F");
  stree->Branch("q22gap1ev",&d_q22gap1ev,"q22gap1ev/F");
  stree->Branch("q22gap1Pev",&d_q22gap1Pev,"q22gap1Pev/F");
  stree->Branch("q22gap1Nev",&d_q22gap1Nev,"q22gap1Nev/F");

  //temp to make smaller files
  //stree->Branch("mom",d_mom,"mom[ntrk]/F");
  //stree->Branch("pt",d_pt,"pt[ntrk]/F");
  //stree->Branch("eta",d_eta,"eta[ntrk]/F");
  //stree->Branch("phi",d_phi,"phi[ntrk]/F");
  //stree->Branch("charge",d_charge,"charge[ntrk]/I");


  // counting histograms

  // matching tuning histograms







  // ---------------------------- //
  // --- Done with Histograms --- //
  // ---------------------------- //



  // --- Now read in the pDSTs listed in the input files
  
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
  nevents += t->GetEntries();





  int n=(int)t->GetEntries(); // number of events in tree
  tree *ktree = new tree(t); // pointer to tree
  for(int i=0;i<n;i++) // loop over events
    {
      
      ktree->GetEntry(i); 

      //int run = ktree->run;
      
      // stringstream ss;
      // ss<<run;
      // int runindex = myMap[ss.str()]; 
      
      
      float zvtx = ktree->zvtx;
      float cent = ktree->v0Cent;
      float cend = ktree->spdCent;
      float cenT = ktree->trkCent;

      hhcent->Fill(cent);
      hhcenT->Fill(cenT);
      hhciff->Fill(cent-cenT);
      hhzvtx->Fill(zvtx);
      
      d_cent = cent;
      d_cend = cend;
      d_cenT = cenT;
      d_zvtx = zvtx;

      const int NTRK = ktree->trackmult;

      if(NTRK>7999)
	{
	  cout<<"too many tracks!"<<endl;
	  continue;
	}

      if(cent==0||cent==100) continue; // float...

      //const int hmax = 9; // now above
      float Xpl[hmax], Ypl[hmax], Xpr[hmax], Ypr[hmax];
      float Xnl[hmax], Ynl[hmax], Xnr[hmax], Ynr[hmax];
      float Xpll[hmax], Ypll[hmax], Xprr[hmax], Yprr[hmax];
      float Xnll[hmax], Ynll[hmax], Xnrr[hmax], Ynrr[hmax];
      float Xa[hmax], Ya[hmax], Xc[hmax], Yc[hmax];
      float wXpl[hmax], wYpl[hmax], wXpr[hmax], wYpr[hmax];
      float wXnl[hmax], wYnl[hmax], wXnr[hmax], wYnr[hmax];
      float wXpll[hmax], wYpll[hmax], wXprr[hmax], wYprr[hmax];
      float wXnll[hmax], wYnll[hmax], wXnrr[hmax], wYnrr[hmax];
      // new
      float tXpl[hmax], tYpl[hmax], tXpr[hmax], tYpr[hmax];
      float tXnl[hmax], tYnl[hmax], tXnr[hmax], tYnr[hmax];
      float tXpll[hmax], tYpll[hmax], tXprr[hmax], tYprr[hmax];
      float tXnll[hmax], tYnll[hmax], tXnrr[hmax], tYnrr[hmax];
      float a1Xp[hmax], a1Yp[hmax], a2Xp[hmax], a2Yp[hmax];
      float a1Xn[hmax], a1Yn[hmax], a2Xn[hmax], a2Yn[hmax];
      float qXp[hmax], qYp[hmax];
      float qXn[hmax], qYn[hmax];
      // end new
      for(int i=0; i<hmax;i++)
	{
	  Xpl[i] = 0.0;
	  Ypl[i] = 0.0;
	  Xpr[i] = 0.0;
	  Ypr[i] = 0.0;
	  Xnl[i] = 0.0;
	  Ynl[i] = 0.0;
	  Xnr[i] = 0.0;
	  Ynr[i] = 0.0;
	  Xpll[i] = 0.0;
	  Ypll[i] = 0.0;
	  Xprr[i] = 0.0;
	  Yprr[i] = 0.0;
	  Xnll[i] = 0.0;
	  Ynll[i] = 0.0;
	  Xnrr[i] = 0.0;
	  Ynrr[i] = 0.0;
	  Xa[i] = 0.0;
	  Ya[i] = 0.0;
	  Xc[i] = 0.0;
	  Yc[i] = 0.0;
	  wXpl[i] = 0.0;
	  wYpl[i] = 0.0;
	  wXpr[i] = 0.0;
	  wYpr[i] = 0.0;
	  wXnl[i] = 0.0;
	  wYnl[i] = 0.0;
	  wXnr[i] = 0.0;
	  wYnr[i] = 0.0;
	  wXpll[i] = 0.0;
	  wYpll[i] = 0.0;
	  wXprr[i] = 0.0;
	  wYprr[i] = 0.0;
	  wXnll[i] = 0.0;
	  wYnll[i] = 0.0;
	  wXnrr[i] = 0.0;
	  wYnrr[i] = 0.0;
	  // new
	  tXpl[i] = 0.0;
	  tYpl[i] = 0.0;
	  tXpr[i] = 0.0;
	  tYpr[i] = 0.0;
	  tXnl[i] = 0.0;
	  tYnl[i] = 0.0;
	  tXnr[i] = 0.0;
	  tYnr[i] = 0.0;
	  tXpll[i] = 0.0;
	  tYpll[i] = 0.0;
	  tXprr[i] = 0.0;
	  tYprr[i] = 0.0;
	  tXnll[i] = 0.0;
	  tYnll[i] = 0.0;
	  tXnrr[i] = 0.0;
	  tYnrr[i] = 0.0;
	  a1Xp[i] = 0.0;
	  a1Yp[i] = 0.0;
	  a1Xn[i] = 0.0;
	  a1Yn[i] = 0.0;
	  a2Xn[i] = 0.0;
	  a2Yn[i] = 0.0;
	  a2Xp[i] = 0.0;
	  a2Yp[i] = 0.0;
	  qXp[i] = 0.0;
	  qYp[i] = 0.0;
	  qXn[i] = 0.0;
	  qYn[i] = 0.0;
	  // end new
	}
      
      
      int ntrk = 0;
      int ntrkpos = 0;
      int ntrkneg = 0;
      int ntrkL = 0;
      int ntrkposL = 0;
      int ntrknegL = 0;
      int ntrkR = 0;
      int ntrkposR = 0;
      int ntrknegR = 0;
      int ntrkC = 0;
      int ntrkposC = 0;
      int ntrknegC = 0;
      int ntrkE = 0;
      int ntrkposE = 0;
      int ntrknegE = 0;
      int ntrkP = 0;
      int ntrkposP = 0;
      int ntrknegP = 0;
      int ntrkT = 0;
      int ntrkposT = 0;
      int ntrknegT = 0;
      int ntrkA1 = 0;
      int ntrkposA1 = 0;
      int ntrknegA1 = 0;
      int ntrkA2 = 0;
      int ntrkposA2 = 0;
      int ntrknegA2 = 0;



      // ----------------------------------
      // ---
      int rind[NTRK];
      for(int i=0; i<NTRK; i++)
	{
	  rind[i] = i;
	}
      srand(time(0)); // make random seed
      for(int i=0; i<(NTRK-1); i++)
        {
	  // random remaining index
          int r = i + (rand() % (NTRK-i));
	  // simple swap algorithm
          int temp = rind[i];
	  rind[i] = rind[r];
	  rind[r] = temp;
        }
      // ---
      // ----------------------------------



      for(int itrk=0; itrk<NTRK; itrk++)
	{
	  ntracks++; // count total number of tracks

	  // number of TPC clusters (60 is minimum for good track reco)
	  if(ktree->track_ncl[itrk]<60) continue;
	  // gets rid of laser tracks
	  if(ktree->track_dedx[itrk]<10) continue;
	  
	  float mom = ktree->track_p[itrk];
	  float pt = ktree->track_pt[itrk];
	  
	  float eta = ktree->track_eta[itrk];
	  float phi = ktree->track_phi[itrk];
	  
	  short charge = ktree->track_q[itrk];

	  // count total number of tracks per event
	  ntrk++;
	  if(charge>0) ntrkpos++;
	  if(charge<0) ntrkneg++;
	  if(eta<0)
	    {
	      ntrkL++;
	      if(charge>0) ntrkposL++;
	      if(charge<0) ntrknegL++;
	    }
	  if(eta>0)
	    {
	      ntrkR++;
	      if(charge>0) ntrkposR++;
	      if(charge<0) ntrknegR++;
	    }
	  if(fabs(eta)<0.5)
	    {
	      ntrkC++;
	      if(charge>0) ntrkposC++;
	      if(charge<0) ntrknegC++;
	    }
	  if(fabs(eta)>0.5)
	    {
	      ntrkE++;
	      if(charge>0) ntrkposE++;
	      if(charge<0) ntrknegE++;
	    }
	  if(pt<0.5)
	    {
	      ntrkP++;
	      if(charge>0) ntrkposP++;
	      if(charge<0) ntrknegP++;
	    }
	  if(pt>0.5)
	    {
	      ntrkT++;
	      if(charge>0) ntrkposT++;
	      if(charge<0) ntrknegT++;
	    }

	  //if(gRandom) delete gRandom;
	  //gRandom = new TRandom3(0);
	  //gRandom->SetSeed(0);
	  //double rand = gRandom->Rndm();
	  //bool sub1 = false;
	  //bool sub2 = false;
	  //if(rand<=0.5) {sub1=true;}
	  //else if(rand>0.5) {sub2=true;}
	  //else{cout<<"huh?"<<endl;continue;}

	  //bool sub1 = false;
	  //bool sub2 = false;
	  //if(rind[itrk]<(NTRK/2.0)) sub1 = true; else sub2 = true;

	  //if(sub1)
	  //{
	  //ntrkA1++;	
	  //if(charge>0) ntrkposA1++;
	  //if(charge<0) ntrknegA1++;
	  //}
	  //if(sub2)
	  //{
	  //ntrkA2++;	
	  //if(charge>0) ntrkposA2++;
	  //if(charge<0) ntrknegA2++;
	  //}



	  hhmom->Fill(mom);
	  hhpt->Fill(pt);

	  float dcaz = ktree->track_dcaz[itrk];
	  float dcaxy = ktree->track_dcaxy[itrk];
	  
	  hhdcaz->Fill(dcaz);
	  hhdcaxy->Fill(dcaxy);

	  //d_mom[ntrk] = ktree->track_p[itrk];
	  //d_pt[ntrk] = ktree->track_pt[itrk];

	  //d_eta[ntrk] = ktree->track_eta[itrk];
	  //d_phi[ntrk] = ktree->track_phi[itrk];

	  //d_charge[ntrk] = ktree->track_q[itrk];
	  

	  // ------------------------------------------
	  // ---
	  // --- q vector information
	  // --- variable format is Xpl[i]
	  // --- X means cos terms, Y means sin terms
	  // --- p means positive, n means negative
	  // --- l means left half of TPC, r means right
	  // --- i is the order of the harmonic
	  // --- the 0th order is a sum
	  // --- X[0] is a sum of the number of particles
	  // --- Y[0] is a sum of the pT values
	  // ---

	  if(pt>0.2&&pt<5.0) // pT selection for fill X Y
	    {
	      if(eta>-0.8&&eta<0.0) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  Xpl[i] += cos(i*phi);
			  Ypl[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  Xnl[i] += cos(i*phi);
			  Ynl[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      Xpl[0] += 1.0;
		      Ypl[0] += pt;
		    }	
		  if(charge<0)
		    {
		      Xnl[0] += 1.0;
		      Ynl[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.0&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  Xpr[i] += cos(i*phi);
			  Ypr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  Xnr[i] += cos(i*phi);
			  Ynr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      Xpr[0] += 1.0;
		      Ypr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      Xnr[0] += 1.0;
		      Ynr[0] += pt;
		    }
		} // end right half of TPC
	      // --------------------------
	      // --- now for larger eta gap
	      // --------------------------
	      if(eta>-0.8&&eta<-0.5) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  Xpll[i] += cos(i*phi);
			  Ypll[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  Xnll[i] += cos(i*phi);
			  Ynll[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      Xpll[0] += 1.0;
		      Ypll[0] += pt;
		    }	
		  if(charge<0)
		    {
		      Xnll[0] += 1.0;
		      Ynll[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.5&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  Xprr[i] += cos(i*phi);
			  Yprr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  Xnrr[i] += cos(i*phi);
			  Ynrr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      Xprr[0] += 1.0;
		      Yprr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      Xnrr[0] += 1.0;
		      Ynrr[0] += pt;
		    }
		} // end right half of TPC
	    } // end of pT selection for fill X Y
	  //-------------- end fill X Y --------------





	  if(pt>0.2&&pt<5.0&&fabs(dcaxy)<0.5&&fabs(dcaz)<0.5) // pT selection for fill wX wY
	    {
	      if(eta>-0.8&&eta<0.0) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  wXpl[i] += cos(i*phi);
			  wYpl[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  wXnl[i] += cos(i*phi);
			  wYnl[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      wXpl[0] += 1.0;
		      wYpl[0] += pt;
		    }	
		  if(charge<0)
		    {
		      wXnl[0] += 1.0;
		      wYnl[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.0&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  wXpr[i] += cos(i*phi);
			  wYpr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  wXnr[i] += cos(i*phi);
			  wYnr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      wXpr[0] += 1.0;
		      wYpr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      wXnr[0] += 1.0;
		      wYnr[0] += pt;
		    }
		} // end right half of TPC
	      // --------------------------
	      // --- now for larger eta gap
	      // --------------------------
	      if(eta>-0.8&&eta<-0.5) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  wXpll[i] += cos(i*phi);
			  wYpll[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  wXnll[i] += cos(i*phi);
			  wYnll[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      wXpll[0] += 1.0;
		      wYpll[0] += pt;
		    }	
		  if(charge<0)
		    {
		      wXnll[0] += 1.0;
		      wYnll[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.5&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  wXprr[i] += cos(i*phi);
			  wYprr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  wXnrr[i] += cos(i*phi);
			  wYnrr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      wXprr[0] += 1.0;
		      wYprr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      wXnrr[0] += 1.0;
		      wYnrr[0] += pt;
		    }
		} // end right half of TPC
	    } // end of pT selection for fill wX wY
	  //-------------- end fill wX wY --------------


	  // new

	  if(pt>0.15&&pt<0.50) // pT selection for fill tX tY
	    {
	      if(eta>-0.8&&eta<0.0) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  tXpl[i] += cos(i*phi);
			  tYpl[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  tXnl[i] += cos(i*phi);
			  tYnl[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      tXpl[0] += 1.0;
		      tYpl[0] += pt;
		    }	
		  if(charge<0)
		    {
		      tXnl[0] += 1.0;
		      tYnl[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.0&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  tXpr[i] += cos(i*phi);
			  tYpr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  tXnr[i] += cos(i*phi);
			  tYnr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      tXpr[0] += 1.0;
		      tYpr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      tXnr[0] += 1.0;
		      tYnr[0] += pt;
		    }
		} // end right half of TPC
	      // --------------------------
	      // --- now for larger eta gap
	      // --------------------------
	      if(eta>-0.8&&eta<-0.5) // left half of TPC
		{
		  // assign values to array elements 1..8
		  for(int i=1; i<hmax;i++)
		    {
		      if(charge>0)
			{
			  tXpll[i] += cos(i*phi);
			  tYpll[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  tXnll[i] += cos(i*phi);
			  tYnll[i] += sin(i*phi);
			}
		    }
		  // assign values to array element 0
		  if(charge>0)
		    {
		      tXpll[0] += 1.0;
		      tYpll[0] += pt;
		    }	
		  if(charge<0)
		    {
		      tXnll[0] += 1.0;
		      tYnll[0] += pt;
		    }
		}
	      //----------------------------
	      if(eta>0.5&&eta<0.8) // right half of TPC
		{
		  for(int i=1; i<hmax; i++)
		    {
		      if(charge>0)
			{
			  tXprr[i] += cos(i*phi);
			  tYprr[i] += sin(i*phi);
			}
		      if(charge<0)
			{
			  tXnrr[i] += cos(i*phi);
			  tYnrr[i] += sin(i*phi);
			}
		    }
		  if(charge>0)
		    {
		      tXprr[0] += 1.0;
		      tYprr[0] += pt;
		    }	
		  if(charge<0)
		    {
		      tXnrr[0] += 1.0;
		      tYnrr[0] += pt;
		    }
		} // end right half of TPC
	    } // end of pT selection for fill tX tY
	  //-------------- end fill tX tY --------------



	  // random stuff used to be here, now below in second track loop

	  // end new


	  
	  //ntrk++; // last line of track loop
	} // End of track loop
      

      int nthrow = 0;
      int ntrkTOTL = 0;
      int ntrkDIFF = 0;
      int chrgMORE = 0;
      int chrgLESS = 0;
      int ntrkLESS = 0;
      int ntrkMORE = 0;
      for(int itrk=0; itrk<NTRK; itrk++)
	{
	  // number of TPC clusters (60 is minimum for good track reco)
	  if(ktree->track_ncl[rind[itrk]]<60) continue;
	  // gets rid of laser tracks
	  if(ktree->track_dedx[rind[itrk]]<10) continue;
	  
	  short charge = ktree->track_q[rind[itrk]];



	  float pt = ktree->track_pt[rind[itrk]];
	  if(pt<0.2||pt>5.0) continue;
	  float eta = ktree->track_eta[rind[itrk]];
	  if(fabs(eta)>0.8) continue; // new...
	  float phi = ktree->track_phi[rind[itrk]];


	  bool sub1 = false;
	  bool sub2 = false;
	  //if(rind[itrk]<(NTRK/2.0)) sub1 = true; else sub2 = true;
	  if(itrk<(NTRK/2.0)) sub1 = true; else sub2 = true;

	  if(sub1)
	    {
	      ntrkA1++;	
	      if(charge>0) ntrkposA1++;
	      if(charge<0) ntrknegA1++;
	    }
	  if(sub2)
	    {
	      ntrkA2++;	
	      if(charge>0) ntrkposA2++;
	      if(charge<0) ntrknegA2++;
	    }


	  

	  if(sub1) // random selection
	    {
	      for(int i=1; i<hmax;i++)
		{
		  if(charge>0)
		    {
		      a1Xp[i] += cos(i*phi);
		      a1Yp[i] += sin(i*phi);
		    }
		  if(charge<0)
		    {
		      a1Xn[i] += cos(i*phi);
		      a1Yn[i] += sin(i*phi);
		    }
		}
	      // assign values to array element 0
	      if(charge>0)
		{
		  a1Xp[0] += 1.0;
		  a1Yp[0] += pt;
		}	
	      if(charge<0)
		{
		  a1Xn[0] += 1.0;
		  a1Yn[0] += pt;
		}
	    }

	  if(sub2) // random selection
	    {
	      for(int i=1; i<hmax;i++)
		{
		  if(charge>0)
		    {
		      a2Xp[i] += cos(i*phi);
		      a2Yp[i] += sin(i*phi);
		    }
		  if(charge<0)
		    {
		      a2Xn[i] += cos(i*phi);
		      a2Yn[i] += sin(i*phi);
		    }
		}
	      // assign values to array element 0
	      if(charge>0)
		{
		  a2Xp[0] += 1.0;
		  a2Yp[0] += pt;
		}	
	      if(charge<0)
		{
		  a2Xn[0] += 1.0;
		  a2Yn[0] += pt;
		}
	    }


	  // now charge equal stuff

	  int Xntrkpos = int(Xpl[0]+Xpr[0]);
	  int Xntrkneg = int(Xnl[0]+Xnr[0]);

	  bool flag = false;
	  if(Xntrkpos>Xntrkneg)
	    {
	      ntrkMORE = Xntrkpos;
	      ntrkLESS = Xntrkneg;
	      chrgMORE = 1;
	      chrgLESS = -1;
	    }
	  if(Xntrkpos<Xntrkneg)
	    {
	      ntrkMORE = Xntrkneg;
	      ntrkLESS = Xntrkpos;
	      chrgMORE = -1;
	      chrgLESS = 1;
	    }
	  if(Xntrkpos==Xntrkneg)
	    {
	      ntrkMORE = Xntrkpos;
	      ntrkLESS = Xntrkneg;
	      flag = true;
	    }

	  ntrkTOTL = ntrkMORE + ntrkLESS;
	  ntrkDIFF = ntrkMORE - ntrkLESS;
	  if(ntrkDIFF<0) {cout<<"what?"<<endl; continue;}

	  if(ntrkLESS<1) continue;
	  if(ntrkMORE<1) continue;
	  //if(ntrkTOTL<1) continue;//department of redundancy department


	  for(int i=1; i<hmax;i++)
	    {
	      if(charge==1&&chrgLESS==1)
		{
		  qXp[i] += cos(i*phi);
		  qYp[i] += sin(i*phi);
		}
	      if(charge==-1&&chrgLESS==-1)
		{
		  qXn[i] += cos(i*phi);
		  qYn[i] += sin(i*phi);
		}
	    }
	  if(charge==1&&chrgLESS==1)
	    {
	      qXp[0] += 1.0;
	      qYp[0] += pt;
	    }	
	  if(charge==-1&&chrgLESS==-1)
	    {
	      qXn[0] += 1.0;
	      qYn[0] += pt;
	    }
	  



	  for(int i=1; i<hmax;i++)
	    {
	      if(charge==1&&chrgMORE==1&&qXp[0]<ntrkLESS)
		{
		  qXp[i] += cos(i*phi);
		  qYp[i] += sin(i*phi);
		}
	      if(charge==-1&&chrgMORE==-1&&qXn[0]<ntrkLESS)
		{
		  qXn[i] += cos(i*phi);
		  qYn[i] += sin(i*phi);
		}
	    }
	  if(charge==1&&chrgMORE==1&&qXp[0]<ntrkLESS)
	    {
	      qXp[0] += 1.0;
	      qYp[0] += pt;
	    }	
	  if(charge==-1&&chrgMORE==-1&&qXn[0]<ntrkLESS)
	    {
	      qXn[0] += 1.0;
	      qYn[0] += pt;
	    }
	      

	} // end of second track loop






      // calculate charge asymmetry for each event
      d_qasymmX = ((Xpl[0]+Xpr[0])-(Xnl[0]+Xnr[0]))/((Xpl[0]+Xpr[0])+(Xnl[0]+Xnr[0]));
      d_qasymLX = (Xpl[0]-Xnl[0])/(Xpl[0]+Xnl[0]);
      d_qasymRX = (Xpr[0]-Xnr[0])/(Xpr[0]+Xnr[0]);
      d_qasymEX = ((Xpll[0]+Xprr[0])-(Xnll[0]+Xnrr[0]))/((Xpll[0]+Xprr[0])+(Xnll[0]+Xnrr[0]));


      float XX[9], YY[9], QQ[9], qq[9];
      float XXp[9], YYp[9], QQp[9], qqp[9]; // pos
      float XXn[9], YYn[9], QQn[9], qqn[9]; // neg
      
      
      for(int i=0; i<6; i++)
	{
	  XX[i]=Xpl[i]+Xnl[i]+Xpr[i]+Xnr[i];
	  YY[i]=Ypl[i]+Ynl[i]+Ypr[i]+Ynr[i];
	  QQ[i]=XX[i]*XX[i]+YY[i]*YY[i];
	  qq[i]=sqrt(QQ[i]/XX[0]);
	  // pos
	  XXp[i]=Xpl[i]+Xpr[i];
	  YYp[i]=Ypl[i]+Ypr[i];
	  QQp[i]=XXp[i]*XXp[i]+YYp[i]*YYp[i];
	  qqp[i]=sqrt(QQp[i]/XXp[0]);
	  // neg
	  XXn[i]=Xnl[i]+Xnr[i];
	  YYn[i]=Ynl[i]+Ynr[i];
	  QQn[i]=XXn[i]*XXn[i]+YYn[i]*YYn[i];
	  qqn[i]=sqrt(QQn[i]/XXn[0]);
	}
      //float mult=XX[0];
      
      
      float M = XX[0];
      float W_2 = M*(M-1);
      float Mp = XXp[0];
      float Wp_2 = Mp*(Mp-1);
      float Mn = XXn[0];
      float Wn_2 = Mn*(Mn-1);

      float Xl2 = Xnl[2]+Xpl[2];
      float Yl2 = Ynl[2]+Ypl[2];
      float Xr2 = Xnr[2]+Xpr[2];
      float Yr2 = Ynr[2]+Ypr[2];
      float Xl0 = Xnl[0]+Xpl[0];
      float Xr0 = Xnr[0]+Xpr[0];
      float Xll2 = Xnll[2]+Xpll[2];
      float Yll2 = Ynll[2]+Ypll[2];
      float Xrr2 = Xnrr[2]+Xprr[2];
      float Yrr2 = Ynrr[2]+Yprr[2];
      float Xll0 = Xnll[0]+Xpll[0];
      float Xrr0 = Xnrr[0]+Xprr[0];

      float q22ev = (QQ[2]-M)/W_2;
      float q22Pev = (QQp[2]-Mp)/Wp_2;
      float q22Nev = (QQn[2]-Mn)/Wn_2;
      float q22gap0ev = (Xl2*Xr2+Yl2*Yr2)/(Xl0*Xr0);
      float q22gap0Pev = (Xpl[2]*Xpr[2]+Ypl[2]*Ypr[2])/(Xpl[0]*Xpr[0]);
      float q22gap0Nev = (Xnl[2]*Xnr[2]+Ynl[2]*Ynr[2])/(Xnl[0]*Xnr[0]);
      float q22gap1ev = (Xll2*Xrr2+Yll2*Yrr2)/(Xll0*Xrr0);
      float q22gap1Pev = (Xpll[2]*Xprr[2]+Ypll[2]*Yprr[2])/(Xpll[0]*Xprr[0]);
      float q22gap1Nev = (Xnll[2]*Xnrr[2]+Ynll[2]*Ynrr[2])/(Xnll[0]*Xnrr[0]);

      d_q22ev  = q22ev;
      d_q22Pev = q22Pev;
      d_q22Nev = q22Nev;
      d_q22gap0ev  = q22gap0ev;
      d_q22gap0Pev = q22gap0Pev;
      d_q22gap0Nev = q22gap0Nev;
      d_q22gap1ev  = q22gap1ev;
      d_q22gap1Pev = q22gap1Pev;
      d_q22gap1Nev = q22gap1Nev;


      // all three should be the same
      // at least one of these causes a floating point exception
      if(ntrkposL<1) continue;
      if(ntrknegL<1) continue;
      if(ntrkposR<1) continue;
      if(ntrknegR<1) continue;
      if(ntrkposC<1) continue;
      if(ntrknegC<1) continue;
      if(ntrkposE<1) continue;
      if(ntrknegE<1) continue;
      if(ntrkposP<1) continue;
      if(ntrknegP<1) continue;
      if(ntrkposT<1) continue;
      if(ntrknegT<1) continue;
      if(ntrkposA1<1) continue;
      if(ntrknegA1<1) continue;
      if(ntrkposA2<1) continue;
      if(ntrknegA2<1) continue;
      //if(ntrk<1) continue;

      //cout<<"num pos is "<<ntrkpos<<endl;
      //cout<<"num neg is "<<ntrkneg<<endl;
      //cout<<"total nums "<<ntrk<<endl;
      
      d_qasymm = (float)(ntrkpos-ntrkneg)/(ntrk);
      d_qasymL = (float)(ntrkposL-ntrknegL)/(ntrkL);
      d_qasymR = (float)(ntrkposR-ntrknegR)/(ntrkR);
      d_qasymC = (float)(ntrkposC-ntrknegC)/(ntrkC);
      d_qasymE = (float)(ntrkposE-ntrknegE)/(ntrkE);
      d_qasymP = (float)(ntrkposP-ntrknegP)/(ntrkP);
      d_qasymT = (float)(ntrkposT-ntrknegT)/(ntrkT);
      d_qasymA1 = (float)(ntrkposA1-ntrknegA1)/(ntrkA1);
      d_qasymA2 = (float)(ntrkposA2-ntrknegA2)/(ntrkA2);

      hqadLR->Fill(d_qasymL-d_qasymR);
      hqadPT->Fill(d_qasymP-d_qasymT);
      hqad12->Fill(d_qasymA1-d_qasymA2);
      
      hhqadLR->Fill(d_qasymL,d_qasymR);
      hhqadPT->Fill(d_qasymP,d_qasymT);
      hhqad12->Fill(d_qasymA1,d_qasymA2);
      
      //cout<<"d_qasymm is "<<d_qasymm<<endl;
      //cout<<"d_qasymL is "<<d_qasymL<<endl;
      //cout<<"d_qasymR is "<<d_qasymR<<endl;

      for(int i=0; i<hmax; i++)
	{
	  d_Xpl[i]=Xpl[i];
	  d_Ypl[i]=Ypl[i];
	  d_Xpr[i]=Xpr[i];
	  d_Ypr[i]=Ypr[i];
	  d_Xnl[i]=Xnl[i];
	  d_Ynl[i]=Ynl[i];
	  d_Xnr[i]=Xnr[i];
	  d_Ynr[i]=Ynr[i];
	  //
	  d_Xpll[i]=Xpll[i];
	  d_Ypll[i]=Ypll[i];
	  d_Xprr[i]=Xprr[i];
	  d_Yprr[i]=Yprr[i];
	  d_Xnll[i]=Xnll[i];
	  d_Ynll[i]=Ynll[i];
	  d_Xnrr[i]=Xnrr[i];
	  d_Ynrr[i]=Ynrr[i];
	  //
	  d_wXpl[i]=wXpl[i];
	  d_wYpl[i]=wYpl[i];
	  d_wXpr[i]=wXpr[i];
	  d_wYpr[i]=wYpr[i];
	  d_wXnl[i]=wXnl[i];
	  d_wYnl[i]=wYnl[i];
	  d_wXnr[i]=wXnr[i];
	  d_wYnr[i]=wYnr[i];
	  //
	  d_wXpll[i]=wXpll[i];
	  d_wYpll[i]=wYpll[i];
	  d_wXprr[i]=wXprr[i];
	  d_wYprr[i]=wYprr[i];
	  d_wXnll[i]=wXnll[i];
	  d_wYnll[i]=wYnll[i];
	  d_wXnrr[i]=wXnrr[i];
	  d_wYnrr[i]=wYnrr[i];
	  // new
	  //
	  d_tXpl[i]=tXpl[i];
	  d_tYpl[i]=tYpl[i];
	  d_tXpr[i]=tXpr[i];
	  d_tYpr[i]=tYpr[i];
	  d_tXnl[i]=tXnl[i];
	  d_tYnl[i]=tYnl[i];
	  d_tXnr[i]=tXnr[i];
	  d_tYnr[i]=tYnr[i];
	  //
	  d_tXpll[i]=tXpll[i];
	  d_tYpll[i]=tYpll[i];
	  d_tXprr[i]=tXprr[i];
	  d_tYprr[i]=tYprr[i];
	  d_tXnll[i]=tXnll[i];
	  d_tYnll[i]=tYnll[i];
	  d_tXnrr[i]=tXnrr[i];
	  d_tYnrr[i]=tYnrr[i];
	  //
	  d_a1Xp[i]=a1Xp[i];
	  d_a1Yp[i]=a1Yp[i];
	  d_a2Xp[i]=a2Xp[i];
	  d_a2Yp[i]=a2Yp[i];
	  d_a1Xn[i]=a1Xn[i];
	  d_a1Yn[i]=a1Yn[i];
	  d_a2Xn[i]=a2Xn[i];
	  d_a2Yn[i]=a2Yn[i];
	  //
	  d_qXp[i]=qXp[i];
	  d_qYp[i]=qYp[i];
	  d_qXn[i]=qXn[i];
	  d_qYn[i]=qYn[i];
	  // end new
	}

      // --- calculate q vectors for V0 detector
      for(int ia=0; ia<32; ia++)
	{
	  float phis = pi/4.0*(ia%8+0.5);
	  int ic = ia+32;
	  for(int i=0; i<hmax; i++)
	    {
	      // V0A (right/forward +2.8<eta<+5.1)
	      Xa[i] += ktree->vzero_cMultV0[ia]*cos(i*phis);
	      Ya[i] += ktree->vzero_cMultV0[ia]*sin(i*phis);
	      // V0C (left/backward -3.7<eta<-1.7)
	      Xc[i] += ktree->vzero_cMultV0[ic]*cos(i*phis);
	      Yc[i] += ktree->vzero_cMultV0[ic]*sin(i*phis);
	    }
	}

      for(int i=0; i<hmax; i++)
	{
	  d_Xa[i]=Xa[i];
	  d_Ya[i]=Ya[i];
	  d_Xc[i]=Xc[i];
	  d_Yc[i]=Yc[i];
	}


      // --- calculate the event planes
      float psia[hmax], psic[hmax], psir[hmax], psil[hmax], psip[hmax], psin[hmax];
      for(int i=1; i<hmax; i++)
        {
          psia[i] = atan2(Ya[i],Xa[i]);
          psic[i] = atan2(Yc[i],Xc[i]);
          psir[i] = atan2(Ypr[i]+Ynr[i],Xpr[i]+Xnr[i]);
          psil[i] = atan2(Ypl[i]+Ynl[i],Xpl[i]+Xnl[i]);
          psip[i] = atan2(Ypr[i]+Ypl[i],Xpr[i]+Xpl[i]);
          psin[i] = atan2(Ynr[i]+Ynl[i],Xnr[i]+Xnl[i]);
        } 
      for(int i=0; i<hmax; i++)
	{
	  d_psia[i]=psia[i];
	  d_psic[i]=psic[i];
	  d_psir[i]=psir[i];
	  d_psil[i]=psil[i];
	  d_psip[i]=psip[i];
	  d_psin[i]=psin[i];
	}
      

      d_ntrk = ntrk;

      // new...
      d_ntrkm = ntrk;
      d_ntrkposm = ntrkpos;
      d_ntrknegm = ntrkneg;
      d_ntrkL = ntrkL;
      d_ntrkposL = ntrkposL;
      d_ntrknegL = ntrknegL;
      d_ntrkR = ntrkR;
      d_ntrkposR = ntrkposR;
      d_ntrknegR = ntrknegR;
      d_ntrkC = ntrkC;
      d_ntrkposC = ntrkposC;
      d_ntrknegC = ntrknegC;
      d_ntrkE = ntrkE;
      d_ntrkposE = ntrkposE;
      d_ntrknegE = ntrknegE;
      d_ntrkP = ntrkP;
      d_ntrkposP = ntrkposP;
      d_ntrknegP = ntrknegP;
      d_ntrkT = ntrkT;
      d_ntrkposT = ntrkposT;
      d_ntrknegT = ntrknegT;
      d_ntrkA1 = ntrkA1;
      d_ntrkposA1 = ntrkposA1;
      d_ntrknegA1 = ntrknegA1;
      d_ntrkA2 = ntrkA2;
      d_ntrkposA2 = ntrkposA2;
      d_ntrknegA2 = ntrknegA2;


      stree->Fill(); // fill for every event
      ngoodevents++;
      if(ngoodevents>=nevcut&&diagnostic)
	{
	  cout<<"Event cut reached, terminating program"<<endl;
	  break;
	}
      //if(i>=nevcut) // name lookup of i changed...
      //{
      //cout<<"Event cut reached, terminating program"<<endl;
      //break;
      //}
    } // End of event loop
  
  // why am i suddenly getting a segfault???
  // t->Delete();
  // delete ktree;
  // f->Close();
  // delete f;
  
  
  
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



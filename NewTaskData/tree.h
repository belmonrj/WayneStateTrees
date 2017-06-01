//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 14 22:14:46 2014 by ROOT version 5.34/08
// from TTree tree/tree
// found on file: TESTX3_single_BIG_OutTaskData.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TObject.h>
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxfTrackGlobal = 3414;
const Int_t kMaxfTrackHybrid = 2357;
const Int_t kMaxfTrackTPCnly = 3414;

class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //Event           *fEvent;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   ULong64_t       offlinetrigger;
   ULong64_t       onlinetrigger;
   Bool_t          isCentral;
   Bool_t          isSemiCentral;
   Bool_t          isMB;
   Float_t         centV0M;
   Float_t         centTRK;
   Float_t         zvtx;
   Int_t           runn;
   Float_t         mag;
   Int_t           vzem;
   Int_t           zdcm;
   Int_t           ntrk;
   Float_t         towerZNA[5];
   Float_t         towerZNC[5];
   Float_t         towerZPA[5];
   Float_t         towerZPC[5];
   Float_t         multV0[64];
   Int_t           fTrackGlobal_;
   UInt_t          fTrackGlobal_fUniqueID[kMaxfTrackGlobal];   //[fTrackGlobal_]
   UInt_t          fTrackGlobal_fBits[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_filter[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_gid[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Bool_t          fTrackGlobal_ishybrid[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_charge[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_p[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_pt[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_eta[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_phi[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_ncls[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_nclsS[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackGlobal_nclsF[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_dcaxy[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_dcaz[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_dedx[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_ttof[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_length[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmapionTPC[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmakaonTPC[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmaprotTPC[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmaelecTPC[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmapionTOF[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmakaonTOF[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmaprotTOF[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Float_t         fTrackGlobal_nsigmaelecTOF[kMaxfTrackGlobal];   //[fTrackGlobal_]
   Int_t           fTrackHybrid_;
   UInt_t          fTrackHybrid_fUniqueID[kMaxfTrackHybrid];   //[fTrackHybrid_]
   UInt_t          fTrackHybrid_fBits[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_filter[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_gid[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Bool_t          fTrackHybrid_ishybrid[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_charge[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_p[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_pt[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_eta[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_phi[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_ncls[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_nclsS[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackHybrid_nclsF[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_dcaxy[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_dcaz[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_dedx[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_ttof[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_length[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmapionTPC[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmakaonTPC[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmaprotTPC[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmaelecTPC[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmapionTOF[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmakaonTOF[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmaprotTOF[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Float_t         fTrackHybrid_nsigmaelecTOF[kMaxfTrackHybrid];   //[fTrackHybrid_]
   Int_t           fTrackTPCnly_;
   UInt_t          fTrackTPCnly_fUniqueID[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   UInt_t          fTrackTPCnly_fBits[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_filter[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_gid[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Bool_t          fTrackTPCnly_ishybrid[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_charge[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_p[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_pt[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_eta[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_phi[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_ncls[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_nclsS[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Int_t           fTrackTPCnly_nclsF[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_dcaxy[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_dcaz[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_dedx[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_ttof[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_length[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmapionTPC[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmakaonTPC[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmaprotTPC[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmaelecTPC[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmapionTOF[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmakaonTOF[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmaprotTOF[kMaxfTrackTPCnly];   //[fTrackTPCnly_]
   Float_t         fTrackTPCnly_nsigmaelecTOF[kMaxfTrackTPCnly];   //[fTrackTPCnly_]

   // List of branches
   TBranch        *b_fEvent_fUniqueID;   //!
   TBranch        *b_fEvent_fBits;   //!
   TBranch        *b_fEvent_offlinetrigger;   //!
   TBranch        *b_fEvent_onlinetrigger;   //!
   TBranch        *b_fEvent_isCentral;   //!
   TBranch        *b_fEvent_isSemiCentral;   //!
   TBranch        *b_fEvent_isMB;   //!
   TBranch        *b_fEvent_centV0M;   //!
   TBranch        *b_fEvent_centTRK;   //!
   TBranch        *b_fEvent_zvtx;   //!
   TBranch        *b_fEvent_runn;   //!
   TBranch        *b_fEvent_mag;   //!
   TBranch        *b_fEvent_vzem;   //!
   TBranch        *b_fEvent_zdcm;   //!
   TBranch        *b_fEvent_ntrk;   //!
   TBranch        *b_fEvent_towerZNA;   //!
   TBranch        *b_fEvent_towerZNC;   //!
   TBranch        *b_fEvent_towerZPA;   //!
   TBranch        *b_fEvent_towerZPC;   //!
   TBranch        *b_fEvent_multV0;   //!
   TBranch        *b_fTrackGlobal_;   //!
   TBranch        *b_fTrackGlobal_fUniqueID;   //!
   TBranch        *b_fTrackGlobal_fBits;   //!
   TBranch        *b_fTrackGlobal_filter;   //!
   TBranch        *b_fTrackGlobal_gid;   //!
   TBranch        *b_fTrackGlobal_ishybrid;   //!
   TBranch        *b_fTrackGlobal_charge;   //!
   TBranch        *b_fTrackGlobal_p;   //!
   TBranch        *b_fTrackGlobal_pt;   //!
   TBranch        *b_fTrackGlobal_eta;   //!
   TBranch        *b_fTrackGlobal_phi;   //!
   TBranch        *b_fTrackGlobal_ncls;   //!
   TBranch        *b_fTrackGlobal_nclsS;   //!
   TBranch        *b_fTrackGlobal_nclsF;   //!
   TBranch        *b_fTrackGlobal_dcaxy;   //!
   TBranch        *b_fTrackGlobal_dcaz;   //!
   TBranch        *b_fTrackGlobal_dedx;   //!
   TBranch        *b_fTrackGlobal_ttof;   //!
   TBranch        *b_fTrackGlobal_length;   //!
   TBranch        *b_fTrackGlobal_nsigmapionTPC;   //!
   TBranch        *b_fTrackGlobal_nsigmakaonTPC;   //!
   TBranch        *b_fTrackGlobal_nsigmaprotTPC;   //!
   TBranch        *b_fTrackGlobal_nsigmaelecTPC;   //!
   TBranch        *b_fTrackGlobal_nsigmapionTOF;   //!
   TBranch        *b_fTrackGlobal_nsigmakaonTOF;   //!
   TBranch        *b_fTrackGlobal_nsigmaprotTOF;   //!
   TBranch        *b_fTrackGlobal_nsigmaelecTOF;   //!
   TBranch        *b_fTrackHybrid_;   //!
   TBranch        *b_fTrackHybrid_fUniqueID;   //!
   TBranch        *b_fTrackHybrid_fBits;   //!
   TBranch        *b_fTrackHybrid_filter;   //!
   TBranch        *b_fTrackHybrid_gid;   //!
   TBranch        *b_fTrackHybrid_ishybrid;   //!
   TBranch        *b_fTrackHybrid_charge;   //!
   TBranch        *b_fTrackHybrid_p;   //!
   TBranch        *b_fTrackHybrid_pt;   //!
   TBranch        *b_fTrackHybrid_eta;   //!
   TBranch        *b_fTrackHybrid_phi;   //!
   TBranch        *b_fTrackHybrid_ncls;   //!
   TBranch        *b_fTrackHybrid_nclsS;   //!
   TBranch        *b_fTrackHybrid_nclsF;   //!
   TBranch        *b_fTrackHybrid_dcaxy;   //!
   TBranch        *b_fTrackHybrid_dcaz;   //!
   TBranch        *b_fTrackHybrid_dedx;   //!
   TBranch        *b_fTrackHybrid_ttof;   //!
   TBranch        *b_fTrackHybrid_length;   //!
   TBranch        *b_fTrackHybrid_nsigmapionTPC;   //!
   TBranch        *b_fTrackHybrid_nsigmakaonTPC;   //!
   TBranch        *b_fTrackHybrid_nsigmaprotTPC;   //!
   TBranch        *b_fTrackHybrid_nsigmaelecTPC;   //!
   TBranch        *b_fTrackHybrid_nsigmapionTOF;   //!
   TBranch        *b_fTrackHybrid_nsigmakaonTOF;   //!
   TBranch        *b_fTrackHybrid_nsigmaprotTOF;   //!
   TBranch        *b_fTrackHybrid_nsigmaelecTOF;   //!
   TBranch        *b_fTrackTPCnly_;   //!
   TBranch        *b_fTrackTPCnly_fUniqueID;   //!
   TBranch        *b_fTrackTPCnly_fBits;   //!
   TBranch        *b_fTrackTPCnly_filter;   //!
   TBranch        *b_fTrackTPCnly_gid;   //!
   TBranch        *b_fTrackTPCnly_ishybrid;   //!
   TBranch        *b_fTrackTPCnly_charge;   //!
   TBranch        *b_fTrackTPCnly_p;   //!
   TBranch        *b_fTrackTPCnly_pt;   //!
   TBranch        *b_fTrackTPCnly_eta;   //!
   TBranch        *b_fTrackTPCnly_phi;   //!
   TBranch        *b_fTrackTPCnly_ncls;   //!
   TBranch        *b_fTrackTPCnly_nclsS;   //!
   TBranch        *b_fTrackTPCnly_nclsF;   //!
   TBranch        *b_fTrackTPCnly_dcaxy;   //!
   TBranch        *b_fTrackTPCnly_dcaz;   //!
   TBranch        *b_fTrackTPCnly_dedx;   //!
   TBranch        *b_fTrackTPCnly_ttof;   //!
   TBranch        *b_fTrackTPCnly_length;   //!
   TBranch        *b_fTrackTPCnly_nsigmapionTPC;   //!
   TBranch        *b_fTrackTPCnly_nsigmakaonTPC;   //!
   TBranch        *b_fTrackTPCnly_nsigmaprotTPC;   //!
   TBranch        *b_fTrackTPCnly_nsigmaelecTPC;   //!
   TBranch        *b_fTrackTPCnly_nsigmapionTOF;   //!
   TBranch        *b_fTrackTPCnly_nsigmakaonTOF;   //!
   TBranch        *b_fTrackTPCnly_nsigmaprotTOF;   //!
   TBranch        *b_fTrackTPCnly_nsigmaelecTOF;   //!

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_cxx
tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TESTX3_single_BIG_OutTaskData.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("TESTX3_single_BIG_OutTaskData.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_fEvent_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_fEvent_fBits);
   fChain->SetBranchAddress("offlinetrigger", &offlinetrigger, &b_fEvent_offlinetrigger);
   fChain->SetBranchAddress("onlinetrigger", &onlinetrigger, &b_fEvent_onlinetrigger);
   fChain->SetBranchAddress("isCentral", &isCentral, &b_fEvent_isCentral);
   fChain->SetBranchAddress("isSemiCentral", &isSemiCentral, &b_fEvent_isSemiCentral);
   fChain->SetBranchAddress("isMB", &isMB, &b_fEvent_isMB);
   fChain->SetBranchAddress("centV0M", &centV0M, &b_fEvent_centV0M);
   fChain->SetBranchAddress("centTRK", &centTRK, &b_fEvent_centTRK);
   fChain->SetBranchAddress("zvtx", &zvtx, &b_fEvent_zvtx);
   fChain->SetBranchAddress("runn", &runn, &b_fEvent_runn);
   fChain->SetBranchAddress("mag", &mag, &b_fEvent_mag);
   fChain->SetBranchAddress("vzem", &vzem, &b_fEvent_vzem);
   fChain->SetBranchAddress("zdcm", &zdcm, &b_fEvent_zdcm);
   fChain->SetBranchAddress("ntrk", &ntrk, &b_fEvent_ntrk);
   fChain->SetBranchAddress("towerZNA[5]", towerZNA, &b_fEvent_towerZNA);
   fChain->SetBranchAddress("towerZNC[5]", towerZNC, &b_fEvent_towerZNC);
   fChain->SetBranchAddress("towerZPA[5]", towerZPA, &b_fEvent_towerZPA);
   fChain->SetBranchAddress("towerZPC[5]", towerZPC, &b_fEvent_towerZPC);
   fChain->SetBranchAddress("multV0[64]", multV0, &b_fEvent_multV0);
   fChain->SetBranchAddress("fTrackGlobal", &fTrackGlobal_, &b_fTrackGlobal_);
   fChain->SetBranchAddress("fTrackGlobal.fUniqueID", fTrackGlobal_fUniqueID, &b_fTrackGlobal_fUniqueID);
   fChain->SetBranchAddress("fTrackGlobal.fBits", fTrackGlobal_fBits, &b_fTrackGlobal_fBits);
   fChain->SetBranchAddress("fTrackGlobal.filter", fTrackGlobal_filter, &b_fTrackGlobal_filter);
   fChain->SetBranchAddress("fTrackGlobal.gid", fTrackGlobal_gid, &b_fTrackGlobal_gid);
   fChain->SetBranchAddress("fTrackGlobal.ishybrid", fTrackGlobal_ishybrid, &b_fTrackGlobal_ishybrid);
   fChain->SetBranchAddress("fTrackGlobal.charge", fTrackGlobal_charge, &b_fTrackGlobal_charge);
   fChain->SetBranchAddress("fTrackGlobal.p", fTrackGlobal_p, &b_fTrackGlobal_p);
   fChain->SetBranchAddress("fTrackGlobal.pt", fTrackGlobal_pt, &b_fTrackGlobal_pt);
   fChain->SetBranchAddress("fTrackGlobal.eta", fTrackGlobal_eta, &b_fTrackGlobal_eta);
   fChain->SetBranchAddress("fTrackGlobal.phi", fTrackGlobal_phi, &b_fTrackGlobal_phi);
   fChain->SetBranchAddress("fTrackGlobal.ncls", fTrackGlobal_ncls, &b_fTrackGlobal_ncls);
   fChain->SetBranchAddress("fTrackGlobal.nclsS", fTrackGlobal_nclsS, &b_fTrackGlobal_nclsS);
   fChain->SetBranchAddress("fTrackGlobal.nclsF", fTrackGlobal_nclsF, &b_fTrackGlobal_nclsF);
   fChain->SetBranchAddress("fTrackGlobal.dcaxy", fTrackGlobal_dcaxy, &b_fTrackGlobal_dcaxy);
   fChain->SetBranchAddress("fTrackGlobal.dcaz", fTrackGlobal_dcaz, &b_fTrackGlobal_dcaz);
   fChain->SetBranchAddress("fTrackGlobal.dedx", fTrackGlobal_dedx, &b_fTrackGlobal_dedx);
   fChain->SetBranchAddress("fTrackGlobal.ttof", fTrackGlobal_ttof, &b_fTrackGlobal_ttof);
   fChain->SetBranchAddress("fTrackGlobal.length", fTrackGlobal_length, &b_fTrackGlobal_length);
   fChain->SetBranchAddress("fTrackGlobal.nsigmapionTPC", fTrackGlobal_nsigmapionTPC, &b_fTrackGlobal_nsigmapionTPC);
   fChain->SetBranchAddress("fTrackGlobal.nsigmakaonTPC", fTrackGlobal_nsigmakaonTPC, &b_fTrackGlobal_nsigmakaonTPC);
   fChain->SetBranchAddress("fTrackGlobal.nsigmaprotTPC", fTrackGlobal_nsigmaprotTPC, &b_fTrackGlobal_nsigmaprotTPC);
   fChain->SetBranchAddress("fTrackGlobal.nsigmaelecTPC", fTrackGlobal_nsigmaelecTPC, &b_fTrackGlobal_nsigmaelecTPC);
   fChain->SetBranchAddress("fTrackGlobal.nsigmapionTOF", fTrackGlobal_nsigmapionTOF, &b_fTrackGlobal_nsigmapionTOF);
   fChain->SetBranchAddress("fTrackGlobal.nsigmakaonTOF", fTrackGlobal_nsigmakaonTOF, &b_fTrackGlobal_nsigmakaonTOF);
   fChain->SetBranchAddress("fTrackGlobal.nsigmaprotTOF", fTrackGlobal_nsigmaprotTOF, &b_fTrackGlobal_nsigmaprotTOF);
   fChain->SetBranchAddress("fTrackGlobal.nsigmaelecTOF", fTrackGlobal_nsigmaelecTOF, &b_fTrackGlobal_nsigmaelecTOF);
   fChain->SetBranchAddress("fTrackHybrid", &fTrackHybrid_, &b_fTrackHybrid_);
   fChain->SetBranchAddress("fTrackHybrid.fUniqueID", fTrackHybrid_fUniqueID, &b_fTrackHybrid_fUniqueID);
   fChain->SetBranchAddress("fTrackHybrid.fBits", fTrackHybrid_fBits, &b_fTrackHybrid_fBits);
   fChain->SetBranchAddress("fTrackHybrid.filter", fTrackHybrid_filter, &b_fTrackHybrid_filter);
   fChain->SetBranchAddress("fTrackHybrid.gid", fTrackHybrid_gid, &b_fTrackHybrid_gid);
   fChain->SetBranchAddress("fTrackHybrid.ishybrid", fTrackHybrid_ishybrid, &b_fTrackHybrid_ishybrid);
   fChain->SetBranchAddress("fTrackHybrid.charge", fTrackHybrid_charge, &b_fTrackHybrid_charge);
   fChain->SetBranchAddress("fTrackHybrid.p", fTrackHybrid_p, &b_fTrackHybrid_p);
   fChain->SetBranchAddress("fTrackHybrid.pt", fTrackHybrid_pt, &b_fTrackHybrid_pt);
   fChain->SetBranchAddress("fTrackHybrid.eta", fTrackHybrid_eta, &b_fTrackHybrid_eta);
   fChain->SetBranchAddress("fTrackHybrid.phi", fTrackHybrid_phi, &b_fTrackHybrid_phi);
   fChain->SetBranchAddress("fTrackHybrid.ncls", fTrackHybrid_ncls, &b_fTrackHybrid_ncls);
   fChain->SetBranchAddress("fTrackHybrid.nclsS", fTrackHybrid_nclsS, &b_fTrackHybrid_nclsS);
   fChain->SetBranchAddress("fTrackHybrid.nclsF", fTrackHybrid_nclsF, &b_fTrackHybrid_nclsF);
   fChain->SetBranchAddress("fTrackHybrid.dcaxy", fTrackHybrid_dcaxy, &b_fTrackHybrid_dcaxy);
   fChain->SetBranchAddress("fTrackHybrid.dcaz", fTrackHybrid_dcaz, &b_fTrackHybrid_dcaz);
   fChain->SetBranchAddress("fTrackHybrid.dedx", fTrackHybrid_dedx, &b_fTrackHybrid_dedx);
   fChain->SetBranchAddress("fTrackHybrid.ttof", fTrackHybrid_ttof, &b_fTrackHybrid_ttof);
   fChain->SetBranchAddress("fTrackHybrid.length", fTrackHybrid_length, &b_fTrackHybrid_length);
   fChain->SetBranchAddress("fTrackHybrid.nsigmapionTPC", fTrackHybrid_nsigmapionTPC, &b_fTrackHybrid_nsigmapionTPC);
   fChain->SetBranchAddress("fTrackHybrid.nsigmakaonTPC", fTrackHybrid_nsigmakaonTPC, &b_fTrackHybrid_nsigmakaonTPC);
   fChain->SetBranchAddress("fTrackHybrid.nsigmaprotTPC", fTrackHybrid_nsigmaprotTPC, &b_fTrackHybrid_nsigmaprotTPC);
   fChain->SetBranchAddress("fTrackHybrid.nsigmaelecTPC", fTrackHybrid_nsigmaelecTPC, &b_fTrackHybrid_nsigmaelecTPC);
   fChain->SetBranchAddress("fTrackHybrid.nsigmapionTOF", fTrackHybrid_nsigmapionTOF, &b_fTrackHybrid_nsigmapionTOF);
   fChain->SetBranchAddress("fTrackHybrid.nsigmakaonTOF", fTrackHybrid_nsigmakaonTOF, &b_fTrackHybrid_nsigmakaonTOF);
   fChain->SetBranchAddress("fTrackHybrid.nsigmaprotTOF", fTrackHybrid_nsigmaprotTOF, &b_fTrackHybrid_nsigmaprotTOF);
   fChain->SetBranchAddress("fTrackHybrid.nsigmaelecTOF", fTrackHybrid_nsigmaelecTOF, &b_fTrackHybrid_nsigmaelecTOF);
   fChain->SetBranchAddress("fTrackTPCnly", &fTrackTPCnly_, &b_fTrackTPCnly_);
   fChain->SetBranchAddress("fTrackTPCnly.fUniqueID", fTrackTPCnly_fUniqueID, &b_fTrackTPCnly_fUniqueID);
   fChain->SetBranchAddress("fTrackTPCnly.fBits", fTrackTPCnly_fBits, &b_fTrackTPCnly_fBits);
   fChain->SetBranchAddress("fTrackTPCnly.filter", fTrackTPCnly_filter, &b_fTrackTPCnly_filter);
   fChain->SetBranchAddress("fTrackTPCnly.gid", fTrackTPCnly_gid, &b_fTrackTPCnly_gid);
   fChain->SetBranchAddress("fTrackTPCnly.ishybrid", fTrackTPCnly_ishybrid, &b_fTrackTPCnly_ishybrid);
   fChain->SetBranchAddress("fTrackTPCnly.charge", fTrackTPCnly_charge, &b_fTrackTPCnly_charge);
   fChain->SetBranchAddress("fTrackTPCnly.p", fTrackTPCnly_p, &b_fTrackTPCnly_p);
   fChain->SetBranchAddress("fTrackTPCnly.pt", fTrackTPCnly_pt, &b_fTrackTPCnly_pt);
   fChain->SetBranchAddress("fTrackTPCnly.eta", fTrackTPCnly_eta, &b_fTrackTPCnly_eta);
   fChain->SetBranchAddress("fTrackTPCnly.phi", fTrackTPCnly_phi, &b_fTrackTPCnly_phi);
   fChain->SetBranchAddress("fTrackTPCnly.ncls", fTrackTPCnly_ncls, &b_fTrackTPCnly_ncls);
   fChain->SetBranchAddress("fTrackTPCnly.nclsS", fTrackTPCnly_nclsS, &b_fTrackTPCnly_nclsS);
   fChain->SetBranchAddress("fTrackTPCnly.nclsF", fTrackTPCnly_nclsF, &b_fTrackTPCnly_nclsF);
   fChain->SetBranchAddress("fTrackTPCnly.dcaxy", fTrackTPCnly_dcaxy, &b_fTrackTPCnly_dcaxy);
   fChain->SetBranchAddress("fTrackTPCnly.dcaz", fTrackTPCnly_dcaz, &b_fTrackTPCnly_dcaz);
   fChain->SetBranchAddress("fTrackTPCnly.dedx", fTrackTPCnly_dedx, &b_fTrackTPCnly_dedx);
   fChain->SetBranchAddress("fTrackTPCnly.ttof", fTrackTPCnly_ttof, &b_fTrackTPCnly_ttof);
   fChain->SetBranchAddress("fTrackTPCnly.length", fTrackTPCnly_length, &b_fTrackTPCnly_length);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmapionTPC", fTrackTPCnly_nsigmapionTPC, &b_fTrackTPCnly_nsigmapionTPC);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmakaonTPC", fTrackTPCnly_nsigmakaonTPC, &b_fTrackTPCnly_nsigmakaonTPC);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmaprotTPC", fTrackTPCnly_nsigmaprotTPC, &b_fTrackTPCnly_nsigmaprotTPC);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmaelecTPC", fTrackTPCnly_nsigmaelecTPC, &b_fTrackTPCnly_nsigmaelecTPC);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmapionTOF", fTrackTPCnly_nsigmapionTOF, &b_fTrackTPCnly_nsigmapionTOF);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmakaonTOF", fTrackTPCnly_nsigmakaonTOF, &b_fTrackTPCnly_nsigmakaonTOF);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmaprotTOF", fTrackTPCnly_nsigmaprotTOF, &b_fTrackTPCnly_nsigmaprotTOF);
   fChain->SetBranchAddress("fTrackTPCnly.nsigmaelecTOF", fTrackTPCnly_nsigmaelecTOF, &b_fTrackTPCnly_nsigmaelecTOF);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_cxx

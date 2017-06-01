// -*-c++-*-
#ifndef AliAnalysisTaskData_cxx
#define AliAnalysisTaskData_cxx

class TList;
class TH1F;
class TProfile;
class TTree;
class TExMap;
class TClonesArray;

//#include "TObject.h"
//#include "AliAnalysisTaskSE.h"



class Event : public TObject
{

 public:

  Event() : TObject() {}

  ULong64_t offlinetrigger;
  ULong64_t onlinetrigger;
  bool  isCentral;
  bool  isSemiCentral;
  bool  isMB;
  float centV0M;
  float centTRK;
  float zvtx;
  int   runn;
  float mag;
  int   vzem;
  int   zdcm;
  int   ntrk_Global;
  int   ntrk_Hybrid;
  int   ntrk_TPCnly;
  float towerZNA[5];
  float towerZNC[5];
  float towerZPA[5];
  float towerZPC[5];
  float multV0[64];
  

  ClassDef(Event, 1);    // Help class
};



class Track : public TObject
{

 public:

  Track() : TObject() {}

  int   filter;
  int   gid;
  int   charge;
  float p;
  float pt;
  float eta;
  float phi;
  int   ncls;
  int   nclsS;
  int   nclsF;
  int   ncross;
  float chi2ndf;
  float dcaxy;
  float dcaz;
  float dedx;
  float ttof;
  float length;
  float nsigmapionTPC;
  float nsigmakaonTPC;
  float nsigmaprotTPC;
  float nsigmaelecTPC;
  float nsigmapionTOF;
  float nsigmakaonTOF;
  float nsigmaprotTOF;
  float nsigmaelecTOF;

  
  ClassDef(Track, 1);    // Help class
};



class AliAnalysisTaskData : public AliAnalysisTaskSE
{
  
 public:
  
  AliAnalysisTaskData(); // default constructor
  AliAnalysisTaskData(const char *name); // additional user defined constructor
  virtual ~AliAnalysisTaskData(){} // default destructor
  
  virtual void UserCreateOutputObjects(); // makes TList and histograms for output
  virtual void UserExec(Option_t *option); // event processor

  ULong64_t trigger; // trigger selection
  ULong64_t GetTrigger(){return trigger;}
  void SetTrigger(const ULong64_t x){trigger = x;}

  int debug; // debug level controls amount of output statements
  int GetDebug(){return debug;}
  void SetDebug(const int x){debug = x;}

  int fbit; // AOD filter bit selection
  int GetFilterBit(){return fbit;}
  void SetFilterBit(const int x){fbit = x;}

  float zvtxcut; // z-vertex selection for collision
  float GetZvtxCut(){return zvtxcut;}
  void SetZvtxCut(const float x){zvtxcut = x;}

  float centcut; // centrality restriction for V0M and TRK
  float GetCentCut(){return centcut;}
  void SetCentCut(const float x){centcut = x;}

  float outeta; // outer eta value for all Q-vector components
  float GetOutEta(){return outeta;}
  void SetOutEta(const float x){outeta = x;}

  float ineta; // inner eta value for gap Q-vector components
  float GetInEta(){return ineta;}
  void SetInEta(const float x){ineta = x;}

  float ptmin; // minimum pt for Q-vector components
  float GetPtMin(){return ptmin;}
  void SetPtMin(const float x){ptmin = x;}
  
  float ptmax; // maximum pt for Q-vector components
  float GetPtMax(){return ptmax;}
  void SetPtMax(const float x){ptmax = x;}
  
  float dcacut; // dca cut for all tracks
  float GetDcaCut(){return dcacut;}
  void SetDcaCut(const float x){dcacut = x;}

  int nclscut; // ncls cut for all tracks
  int GetNclsCut(){return nclscut;}
  void SetNclsCut(const float x){nclscut = x;}

 private:

  // something;

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
  
  TList *fOutputList;//!
  TH1F *fHistDCACOVerrors;//!
  TH1F *fHistPt;//!
  TH1F *fHistPhi;//!
  TH1F *fHistEta;//!
  TH1F *fHistCharge;//! 
  TH1F *fHistTPCncls;//!
  TH1F *fHistDedxTPC;//!
  TH1F *fHistDCAxy;//!
  TH1F *fHistDCAz;//!
  TH1F *fHistZVtx;//!
  TH1F *fHistZVtxD;//!
  TH1F *fHistCentTRK;//!
  TH1F *fHistCentV0M;//!
  TH1F *fHistCentTRKkSel;//!
  TH1F *fHistCentV0MkSel;//!


  TExMap *trackMap;//!
  TExMap *hybridMap;//!



   
  AliAnalysisTaskData(const AliAnalysisTaskData&); // copy constructor not implemented
  AliAnalysisTaskData& operator=(const AliAnalysisTaskData&); // assignment operator not implemented
  
  ClassDef(AliAnalysisTaskData, 1); // Add this class as ROOT class (inherit from TObject)
};

#endif

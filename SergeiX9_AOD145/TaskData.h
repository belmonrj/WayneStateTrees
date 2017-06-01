// -*-c++-*-
#ifndef TaskData_cxx
#define TaskData_cxx


class TTree;
class TClonesArray;


class Event : public TObject
{

 public:

  Event();
  ~Event();

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
  int   ntrk_gbl;
  int   ntrk_hyb;
  int   ntrk_tpc;
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

  Track();
  ~Track();

  int   filter;
  int   gid;
  int   charge;
  float tpcmom;
  float p;
  float pt;
  float eta;
  float phi;
  int   ncls;
  int   nclsS;
  int   nclsF;
  int   ncross;
  float chi2pc;
  float dcaxy;
  float dcaz;
  float dedx;
  float ttof;
  float length;
  float nspiTPC;
  float nskTPC;
  float nspTPC;
  float nseTPC;
  float nspiTOF;
  float nskTOF;
  float nspTOF;
  float nseTOF;

  
  ClassDef(Track, 1);    // Help class
};





  
#endif


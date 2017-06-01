void runGrid()
{

  gSystem->Load("libCore.so");  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");   
  gROOT->ProcessLine(".include $ROOTSYS/include");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");



  gROOT->LoadMacro("CreateAlienHandler.C");
  AliAnalysisGrid *alienH = CreateAlienHandler();  
  if(!alienH) return;
  AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskData");
  mgr->SetGridHandler(alienH);
  AliAODInputHandler *aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

  // --- add other AddTask macros here!
  gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  AddTaskPIDResponse(kTRUE); // ???
  //AddTaskPIDResponse(0); // ???



  cout<<"Memory address of AliAnalysisManager is "<<mgr<<endl;

  gROOT->LoadMacro("AliAnalysisTaskData.cxx++g");   



  // ------------------------------------ //
  // --- AddTask should start here... --- //
  // ------------------------------------ //

  // AliAnalysisTask *task = new AliAnalysisTaskData("TaskData");
  // mgr->AddTask(task);
  // AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();
  // AliAnalysisDataContainer *coutput = mgr->CreateContainer("chist",
  // 							   TList::Class(),
  // 							   AliAnalysisManager::kOutputContainer,
  // 							   "test.root");
  // mgr->ConnectInput(task,0,cinput);
  // mgr->ConnectOutput(task,1,coutput);

  // --- these line replaces the preceding lines ------------------------------------
  gROOT->LoadMacro("AddTaskData.C");
  // --- MUST call AddTask to process
  AliAnalysisTaskData *ptr = AddTaskData();
  if(ptr) cout<<"Success!  AddTask = "<<ptr<<endl;
  else cout<<"Failure!  Could not add task, prepare for ultimate suffering..."<<endl;
  // --------------------------------------------------------------------------------

  // ---------------------------------- //
  // --- AddTask should end here... --- //
  // ---------------------------------- //


  int debug = ptr->GetDebug();
  //int debug = 2;
  mgr->SetDebugLevel(debug);
  if(!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  mgr->StartAnalysis("grid");

}

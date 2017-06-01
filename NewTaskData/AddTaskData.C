AliAnalysisTaskData *AddTaskData
(
 int debug = 3,
 ULong64_t trigger = AliVEvent::kMB|AliVEvent::kSemiCentral,
 int fbit = 16383,
 //int fbit = 128,
 float zvtxcut = 15.0,
 char *name = "TaskData"
)
{


  // --- get analysis manager
  AliAnalysisManager *aam = AliAnalysisManager::GetAnalysisManager();
  if(!aam) 
    {
      cout<<"No analysis manager, now dying..."<<endl;
      return NULL;
    }  
  cout<<"Memory address of AliAnalysisManager is "<<aam<<endl;


  // --- check that input handler exists
  if(!aam->GetInputEventHandler())
    {
      cout<<"No input even handler, now dying..."<<endl;
      return NULL;
    }   


  // --- instantiate analysis task
  AliAnalysisTaskData *task = new AliAnalysisTaskData(name);
  cout<<"Memory address of task is "<<task<<endl;
  // // --- set parameters
  // task->SetParameters();
  // // --- set task methods as needed
  task->SetDebug(debug);
  // task->SetDoMC(doMC);
  task->SetTrigger(trigger);
  // task->SetDoEffCorrection(doeffcorr);
  // task->SetCentHandle(centhandle);
  task->SetFilterBit(fbit);
  task->SetZvtxCut(zvtxcut);
  // task->SetCentCut(centcut);
  // task->SetNclsCut(nclscut);
  // task->SetDCAcutZ(dcacutz);
  // task->SetDCAcutXY(dcacutxy);
  // task->SetDoDCAcuts(dodcacuts);
  // task->SetOutEta(outeta);
  // task->SetInEta(ineta);
  // task->SetExclEta(excleta);
  // task->SetPtMin(ptmin);
  // task->SetPtMax(ptmax);
  // task->SetDoAcuts(doacuts);
  // task->SetSigmaPID(nspid);
  // task->SetCentBinLow(cbinlo);
  // task->SetCentBinHigh(cbinhi);
  // task->SetDoNested(donested);
  // task->SetDoPairCut(dopaircut);
  // task->SetCentDCLow(centlo);
  // task->SetCentDCHigh(centhi);


  // --- get input and output managers
  AliAnalysisDataContainer *aadci = aam->GetCommonInputContainer();
  AliAnalysisDataContainer *aadco = aam->CreateContainer
    (
     Form("List%s",name), 
     TList::Class(),    
     AliAnalysisManager::kOutputContainer, 
     //Form("Out%s_%s",name,AliAnalysisManager::GetCommonFileName())
     Form("Out%s.root",name)
     //Form("OutHistos%s.root",name)
     );
  // observe that ".root" is automatically appended
  AliAnalysisDataContainer *aadct = aam->CreateContainer
    (
     Form("Tree%s",name), 
     TTree::Class(),    
     AliAnalysisManager::kOutputContainer, 
     Form("Out%s.root",name)
     //Form("OutTree%s.root",name)
     //Form("TreeOut%s_%s",name,AliAnalysisManager::GetCommonFileName())
     );
  // observe that ".root" is automatically appended


  // --- add task and connect input and output managers
  aam->AddTask(task);
  aam->ConnectInput(task,0,aadci);
  aam->ConnectOutput(task,1,aadco);
  aam->ConnectOutput(task,2,aadct);

  // --- return pointer to Task
  return task;

}

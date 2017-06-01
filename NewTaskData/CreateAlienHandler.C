AliAnalysisGrid *CreateAlienHandler()
{

  AliAnalysisAlien *plugin = new AliAnalysisAlien();
  plugin->SetOverwriteMode();

  // Set the run mode (can be "full", "test", "offline", "submit" or "terminate")
  plugin->SetRunMode("test");
  //plugin->SetRunMode("full");
  //plugin->SetRunMode("terminate");

  // Set versions of used packages
  plugin->SetAPIVersion("V1.1x");
  // --- old laptop version
  // plugin->SetROOTVersion("v5-34-05");
  // plugin->SetAliROOTVersion("v5-04-68-AN");
  // --- new laptop version
  //plugin->SetROOTVersion("v5-34-08");
  //plugin->SetAliROOTVersion("v5-05-77-AN"); // FUCK
  //plugin->SetROOTVersion("v5-34-08-6");
  //plugin->SetAliROOTVersion("vAN-20140602");
  plugin->SetROOTVersion("v5-34-19");
  plugin->SetAliROOTVersion("vAN-20140729");
   

  
  // ------------------------------------------ //
  // --- Declare input data to be processed --- //
  // ------------------------------------------ //

  // Method 1: Create automatically XML collections using alien 'find' command.
  // Define production directory LFN
  //plugin->SetGridDataDir("/alice/sim/LHC10a6");
  // On real reconstructed data:
  // plugin->SetGridDataDir("/alice/data/2009/LHC09d");
  // Set data search pattern
  //plugin->SetDataPattern("*ESDs.root");
  // Data pattern for reconstructed data
  //plugin->SetDataPattern("*ESDs/pass4/*ESDs.root");
  //plugin->SetRunPrefix("000");   // real data
  // Then add run numbers to be considered
  //plugin->AddRunNumber(125020);
  
  // ----------------------------------
  // --- for analyzing LHC13d2 sim data  
  // ----------------------------------
  // plugin->SetGridDataDir("/alice/sim/2013/LHC13d2/");
  // //plugin->SetDataPattern("AOD/001/AliAOD.root"); // one possibility
  // plugin->SetDataPattern("AOD/*/AliAOD.root"); // one possibility
  // //plugin->SetDataPattern("001/AliAOD.root"); // another possibility
  // //plugin->SetDataPattern("*/AliAOD.root"); // another possibility
  // //plugin->SetRunPrefix("000");// not for sim
  // //plugin->AddRunNumber(137161); 
  // gROOT->ProcessLine(".L AddRunNumbers.C");
  // int added = AddRunNumbers(plugin,0,95,"lhc13d2"); // 
  // if(added<0) return NULL;

  // ----------------------------------
  // --- for analyzing LHC12a11* sim data  
  // ----------------------------------
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11a/");//0-10?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11b/");//10-20?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11c/");//20-30?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11d/");//30-40?
  // plugin->SetGridDataDir("/alice/sim/2012/LHC12a11e/");//40-50?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11f/");//50-60?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11g/");//60-70?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11h/");//70-80?
  // //plugin->SetGridDataDir("/alice/sim/2012/LHC12a11i/");//80-90?
  // //plugin->SetDataPattern("AOD157/0001/AliAOD.root");
  // plugin->SetDataPattern("AOD157/*/AliAOD.root");
  // //plugin->SetRunPrefix("000");// not for sim
  // plugin->AddRunNumber(137686); 
  // plugin->AddRunNumber(138534); 
  // plugin->AddRunNumber(138653); 
  // plugin->AddRunNumber(139038); 
  // plugin->AddRunNumber(139437); 

  // ------------------------------------
  // --- for analyzing LHC11a10a sim data  
  // ------------------------------------
  // plugin->SetGridDataDir("/alice/sim/LHC11a10a_bis/");
  // plugin->SetDataPattern("AOD143/0001/AliAOD.root");
  // //plugin->SetDataPattern("AOD143/*/AliAOD.root");
  // //plugin->SetRunPrefix("000");// not for sim
  // plugin->AddRunNumber(137161); 
  // gROOT->ProcessLine(".L AddRunNumbers.C");
  // int added = AddRunNumbers(plugin,0,95,"lhc11a10a"); // 
  // if(added<0) return NULL;

  // ----------------------------------
  // --- for analyzing LHC10h real data  
  // ----------------------------------
  // plugin->SetGridDataDir("/alice/data/2010/LHC10h/");
  // //plugin->SetDataPattern("ESDs/pass2/AOD086/*/AliAOD.root"); // for testing over multiple files
  // //plugin->SetDataPattern("ESDs/pass2/AOD086/0001/AliAOD.root"); // for testing over a single file
  // //plugin->SetDataPattern("ESDs/pass2/AOD160/*/AliAOD.root"); // for testing over a single file
  // plugin->SetDataPattern("ESDs/pass2/AOD160/0001/AliAOD.root"); // for testing over a single file
  // plugin->SetRunPrefix("000");
  // plugin->AddRunNumber(137161); 
  // gROOT->ProcessLine(".L AddRunNumbers.C");
  // int added = AddRunNumbers(plugin,0,90,"lhc10h");
  // if(added<0) return NULL;
  
  // ----------------------------------
  // --- for analyzing LHC11h real data  
  // ----------------------------------
  plugin->SetGridDataDir("/alice/data/2011/LHC11h_2/");
  //plugin->SetDataPattern("ESDs/pass2/AOD145/0001/AliAOD.root"); // for testing over a single file
  //plugin->SetDataPattern("ESDs/pass2/AOD145/*/AliAOD.root");
  plugin->SetDataPattern("ESDs/pass2/AOD115/0001/AliAOD.root"); // for testing over a single file
  //plugin->SetDataPattern("ESDs/pass2/AOD115/*/AliAOD.root");
  plugin->SetRunPrefix("000");
  plugin->AddRunNumber(168464); 
  //gROOT->ProcessLine(".L AddRunNumbers.C");
  //int added = AddRunNumbers(plugin,0,10,"lhc11h");
  //int added = AddRunNumbers(plugin,0,2,"lhc11h");
  //if(added<0) return NULL;

  // ------------------------------------------ //
  // --- Set the paths for the working area --- //
  // ------------------------------------------ //
  
  plugin->SetGridWorkingDir("TaskData"); // $HOME/TaskData
  plugin->SetGridOutputDir("TrialRunX8_LHC11h_AOD145"); // 
  //plugin->SetGridOutputDir("TrialRun5_LHC11h_AOD145"); // 
  //plugin->SetGridOutputDir("TrialRun_LHC11h_AOD115"); // 



  // -------------------------------------------------------------- //
  // --- Declare the analysis class definition and header files --- //
  // -------------------------------------------------------------- //

  plugin->SetAnalysisSource("AliAnalysisTaskData.cxx"); // class file
  plugin->SetAdditionalLibs("AliAnalysisTaskData.h AliAnalysisTaskData.cxx"); // header space class
  plugin->SetDefaultOutputs(); // ALWAYS use default outputs, code warns then crashes if not



  // ------------------------------------------------- //
  // --- Now for a wide array of optional settings --- //
  // ------------------------------------------------- //

  plugin->SetSplitMaxInputFileNumber(100); // default 100 input files/subjob
  //plugin->SetMaxInitFailed(5); // default (?) jobs fail to kill waiting subjobs
  //plugin->SetMasterResubmitThreshold(90); // default (?) resubmit threshold
  plugin->SetTTL(50000); // default 30000 sec time to live
  plugin->SetAnalysisMacro("TaskData.C"); // default "MyAnalysis.C"
  plugin->SetExecutable("TaskData.sh"); // default "analysis.sh"
  plugin->SetJDLName("TaskData.jdl"); // default "analysis.jdl"
  plugin->SetInputFormat("xml-single"); // default "xml-single"
  plugin->SetPrice(1); // default 1 price to modify job
  plugin->SetSplitMode("se"); // default "se"



  return plugin;

}

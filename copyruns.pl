#!/usr/bin/perl

open(FIN1,"<runs_lhc11h.list") or die "cannot open file for reading \n"; #open for reading

$counter = 0;
$kounter = 0;
while(<FIN1>)
{

    # ---------------------------------------------------------------------- #
    # --- extra counter to increment runnumber but not file index number --- #
    $kounter = $kounter + 1;
    next if $kounter < 11;
    # ---------------------------------------------------------------------- #

    last if $counter > 9;

    $string = "0".$counter;
    if($counter<10)
    {
	$string = "00".$counter;
    }

    chomp($_); # if you comment out this line**                                                                                                                

    $runn = $_;

    print "directory number ".$string." is run number ".$runn." \n"; 





    $stringmain = "alien:///alice/cern.ch/user/r/rbelmont/TaskData/TrialRunX9_LHC11h_AOD145/".$string."/";
    $stringmain2 = "/alice/cern.ch/user/r/rbelmont/TaskData/TrialRunX9_LHC11h_AOD145/".$string."/";
    $stringname = "/OutTaskData.root";
    
    @segments = `alien_ls $stringmain2`;
    
    foreach (@segments)
    {
	
	chomp($_);
	$stringsegment = $_;
	#$stringsegment = $_;
	#chomp($stringsegment);
	
	$stringfinal = $stringmain.$stringsegment.$stringname;
	
	#$destination = "TrialRunX9_AOD145/WSUlocaldataX9_LHC11h_AOD145_".$string."-".$stringsegment.".root";
	$destination = "TrialRunX9_AOD145/WSUlocaldataX9_LHC11h_AOD145_".$runn."-".$stringsegment.".root";
	
	print "command to be executed is: \nalien_cp $stringfinal \n$destination \n\n";
	#system("alien_cp $stringfinal $destination");
	
	
    }

    
    
    
    $counter = $counter + 1;
    #next if $counter < 2;
    


}
close FIN1;

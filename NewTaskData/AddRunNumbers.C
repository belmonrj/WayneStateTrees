int AddRunNumbers(AliAnalysisAlien *plugin, int start=0, int number=1, char *handle="lhc10h")
{

  if(plugin==NULL)
    {
      cout<<"plugin is NULL"<<endl;
      cout<<"cannot add run numbers"<<endl;
      return -1;
    }

  const int maxnruns = 200;
  int runn[maxnruns];
  char filename[20];
  sprintf(filename,"runs_%s.list",handle);

  ifstream fin;
  fin.open(filename);
  if(!fin.is_open())
    {
      cout<<"cannot open run list file "<<filename<<endl;
      cout<<"cannot add run numbers"<<endl;
      return -1;
    }

  int nrun=0;
  while(!fin.eof())
    fin>>runn[nrun++];

  nrun -=1;
  int nadd = number+start>nrun?nrun-start:number;
  for(int i=start; i<nadd+start; i++)
    {
      plugin->AddRunNumber(runn[i]);
    }

  cout<<"Added "<<nadd<<" runs to plugin"<<endl;

  return 0;

}

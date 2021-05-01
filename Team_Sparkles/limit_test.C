/*limit_test.C
  Author: Alan Mendez
  7/27/16
  Read data concerning wiringPi period calculations
  from a txt file (limit_test.txt), create a root file
  with a Tree, and create multiple histograms and graphs of the data.
*/

{
  gROOT->Reset();

  //open the txt file
  ifstream in;
  in.open("limit_test.txt");

  //create a TFile
  TFile *file = new TFile("limit_test.root", "RECREATE", "limit_test");

  //data elements
  Double_t T;//expected period (nanoseconds)
  Double_t d;//measured period (nanoseconds)
 
  //The input file limit_test.txt is a table
  //of calculated periods at various set periods
   
  //create a TTree
  TTree *tree = new TTree("limit_test","High Resolution Test Data in Nanoseconds");
  tree->Branch("T",&T,"T/L");
  tree->Branch("d",&d,"d/L");
 
  while (1)
    {
      if (!in.good()) break;
      in >> T >> d;
 
      //fill the TTree
      tree->Fill();
      tree->Show();
      cout << endl;
      
    }
  in.close();
  tree->Write();

 //create an array of histogram objects
  TObjArray limits2(0);

  int i = 0;
  int b = 100;

  while(b < 1200)
    {
      TH1 *h = new TH1I("h","new",100, 1000, 4000);
      while(i < b)
	{
	  limit_test.GetEntry(i);
	  h->Fill(d);
	  // h->SetBit(TH1::kCanRebin); //autoadjust bin size
	  i = i + 1;
	}
      limits2.Add(h); //add histogram to the array
      b +=100;
    }

  //open a file and write the array to the file
      TFile *histfile = new TFile("limits2.root", "recreate", "limits2");
  limits2.Write();
}
}

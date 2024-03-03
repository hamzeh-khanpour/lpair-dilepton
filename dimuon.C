#define dimuon_cxx
#include "dimuon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void dimuon::Loop()
{
//   In a ROOT session, you can do:
//      root> .L dimuon.C
//      root> dimuon t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<10;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

  
//      cout << "npart = " << npart << endl;
      
      
//        cout << "eta[npart] = "      << eta[5] << endl; 
//        cout << "rapidity[npart] = " << rapidity[5] << endl;         
//        cout << "pt[npart] = "       << pt[5] << endl;               
//        cout << "m[npart] = "        << m[5] << endl;    
//        cout << "charge[npart] = "   << charge[5] << endl; 
        cout << "pdg_id[npart] = "   << pdg_id[5] << endl; 


// 0 = proton
// 1 = electron
// 2 = photon
// 3 = photon   
// 4 = proton
// 5 = muon
// 6 = muon  
// 7 = muon
// 8 = electron
            
            
          
}
}

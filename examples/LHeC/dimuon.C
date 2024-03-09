//
// ***************************** exclusive production of dimuons ******************************
//


// Stdlib header file for input and output
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>


// include statements for all needed dependencies
#include "TH1F.h"
#include "TTree.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TVirtualFitter.h"
#include "TMath.h"
#include "stdlib.h"
#include "math.h"
#include "TPaveText.h"
#include <string>
#include <vector>
#include "TVirtualFitter.h"
#include "TBranch.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "TGraph.h"
#include "TFrame.h"
#include "TAttFill.h"
#include "TNamed.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TRandom3.h"
#include "THStack.h"
#include "TLegend.h"
#include "TSystem.h"
#include "TInterpreter.h"
#include "Math/LorentzVector.h"


#define dimuon_cxx
#include "dimuon.h"


    TFile *target;
    TTree *Tsignal_LHeC = new TTree("LHeC_dimuon","LHeC_dimuon");
    TFile *F;


// **********************************************************************   
// Book Histograms 
// **********************************************************************   

    TH1 *histMassdilepton  =  new TH1F("M_{inv}", "",   30, 0.0, 10.0);
    TH1 *histPtdilepton    =  new TH1F("Ptll", "",      30, 0.0, 10.0);
    TH1 *histetall         =  new TH1F("etall", "",     30, -5.0, 5.0); 
    TH1 *histYll           =  new TH1F("Yll", "",       30, -5.0, 5.0);
    TH1 *histThetall       =  new TH1F("Thetall", "",   30, -5.0, 5.0);


    TLorentzVector lepton1;
    TLorentzVector lepton2;
    TLorentzVector MydiLepton;

    TLorentzVector lepton12;
    TLorentzVector MydiLepton12;

    vector <TLorentzVector> l1;
    vector <TLorentzVector> l2;
    vector <TLorentzVector> l1l2;


    Float_t Mll     = 0.0;
    Float_t Ptll    = 0.0;
    Float_t Etall   = 0.0;
    Float_t Yll     = 0.0;
    Float_t Thetall = 0.0;

    Float_t Mmu     = 105.66 * 1.0/1000.0;


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


    l1.clear();
    l2.clear();
    l1l2.clear();


    Tsignal_LHeC->Branch("Mll",&Mll);
    Tsignal_LHeC->Branch("Ptll",&Ptll);
    Tsignal_LHeC->Branch("Etall",&Etall);
    Tsignal_LHeC->Branch("Yll",&Yll);
    Tsignal_LHeC->Branch("Thetall",&Thetall);


    gStyle->SetOptStat(0);  
    
    
 if (fChain == 0) return;


   Long64_t nentries = fChain->GetEntriesFast();


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry < nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;


//        cout << "npart = " << npart << endl; 
//        cout << "eta[npart] = "      << eta[5] << endl;  
//        cout << "rapidity[npart] = " << rapidity[5] << endl;          
//        cout << "pt[npart] = "       << pt[5] << endl;                
//        cout << "m[npart] = "        << m[5] << endl;     
//        cout << "charge[npart] = "   << charge[5] << endl;  
//        cout << "pdg_id[npart] = "   << pdg_id[6] << endl;   


// 0 = proton
// 1 = electron
// 2 = photon
// 3 = photon   
// 4 = proton
// 5 = muon   First  muon  
// 6 = muon   gamma gamma -> mu+ mu-   
// 7 = muon   Second muon 
// 8 = electron



      if (charge[5] == 1) {

  lepton1.SetPtEtaPhiE( pt[5], eta[5], phi[5], E[5] );
      } else if (charge[7] == 1) {

    lepton1.SetPtEtaPhiE( pt[7], eta[7], phi[7], E[7] );
}

      if (charge[5] == -1) {

  lepton2.SetPtEtaPhiE( pt[5], eta[5], phi[5], E[5] );
      } else if (charge[7] == -1) {

    lepton2.SetPtEtaPhiE( pt[7], eta[7], phi[7], E[7] );
}



  lepton12.SetPtEtaPhiE( pt[6], eta[6], phi[6], E[6] );



//    lepton1.SetPtEtaPhiE( pt[5], eta[5], phi[5], E[5] );
    l1.push_back(lepton1);

//    lepton2.SetPtEtaPhiE( pt[7], eta[7], phi[7], E[7] );
    l2.push_back(lepton2);



//    MydiLepton   = lepton1  + lepton2;
    MydiLepton   = lepton12;
//    MydiLepton12 = lepton12;

    l1l2.push_back(MydiLepton);


//  cout << l1l2.size()  << endl;




//for(unsigned int j=1; j<l1l2.size();j++)
//      {
//      cout << l1l2[j].Eta()  << endl;
//      Etall = l1l2[j].Eta();
//      }


/*

  Mll   =  lepton1.M()   + lepton2.M();
  Ptll  =  lepton1.Pt()  + lepton2.Pt();
  Etall =  lepton1.Eta() + lepton2.Eta();

*/

    Mll     =  MydiLepton.M();
    Ptll    =  MydiLepton.Pt();
    Etall   =  MydiLepton.Eta();
    Thetall =  MydiLepton.Theta();


//    Etall = -TMath::Log(TMath::Tan(Thetall / 2.0));

    // Calculate rapidity using: y = 1/2 ln ( (E+Pz)/(E-Pz) )
//    Yll = 1.0/2.0 * TMath::Log( (MydiLepton.E() + MydiLepton.Pz()) / (MydiLepton.E() - MydiLepton.Pz()) );

    // Calculate rapidity using: y = Eta - cos(Theta)/2 (m/p_T)^2
    Yll = Etall -  TMath::Cos(Thetall)/2.0 * (Mmu/Ptll)* (Mmu/Ptll);


//  cout << " Mll   = "  << Mll << endl;
//  cout << " Ptll  = "  << Ptll << endl;
//  cout << " Etall = "  << Etall << endl;


    histMassdilepton->Fill(Mll);      
    histPtdilepton->Fill(Ptll);
    histetall->Fill(Etall);
    histYll->Fill(Yll);
    histThetall->Fill(Thetall);

      
    Tsignal_LHeC->Fill();
          
}


    target = new TFile ("LHeC_dimuon.root","recreate");
    target->cd();

    Tsignal_LHeC->Write();

    target->Close();

     

// =======================================================================
// =======================================================================
// =======================================================================


Double_t xl1=0.70, yl1=0.70, xl2=xl1+0.10, yl2=yl1+0.250; 

TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
leg->SetBorderSize(0);

leg->AddEntry(histMassdilepton,"e p #rightarrow e #mu^{-}#mu^{+} p","L")->SetTextColor(kBlue+1);

leg->SetTextSize(0.032);
leg->SetTextFont(12);
leg->SetFillStyle(0);

//    (#sqrt{s} = 365 GeV, L_{int} = 1.5 ab^{-1})    1.5 ab^{-1} (365 GeV)

TLatex *t2a = new TLatex(0.5,0.9,"#bf{NPART 6 = MUON1->2}"); 
                t2a->SetNDC();
                t2a->SetTextFont(42);
                t2a->SetTextSize(0.04);
                t2a->SetTextAlign(20);

                
TLatex *t3a = new TLatex(0.27,0.85,"E_{e} = 18 GeV");
                t3a->SetNDC();
                t3a->SetTextFont(42);
                t3a->SetTextSize(0.04);
                t3a->SetTextAlign(20);
                
            
TLatex *t4a = new TLatex(0.276,0.80,"E_{p} = 275 GeV");
                t4a->SetNDC();
                t4a->SetTextFont(42);
                t4a->SetTextSize(0.04);
                t4a->SetTextAlign(20);


TLatex *t5a = new TLatex(0.666,0.66,"#gamma-tagged (low-mass sample)");
                t5a->SetNDC();
                t5a->SetTextFont(12);
                t5a->SetTextSize(0.04);
                t5a->SetTextAlign(20);
                
TLatex *t6a = new TLatex(0.692,0.61,"hadron_polarisation = 0|0|1");
                t6a->SetNDC();
                t6a->SetTextFont(12);
                t6a->SetTextSize(0.04);
                t6a->SetTextAlign(20);
                
TLatex *t2b = new TLatex(0.70,0.550,"0.5<E'_{e}/E_{e}<0.90 & #pi-#theta_{e}<10 mrad");
                t2b->SetNDC();
                t2b->SetTextFont(12);
                t2b->SetTextSize(0.04);
                t2b->SetTextAlign(20);

                
TLatex *t3b = new TLatex(0.64,0.50,"x_{L}<0.97 || p_{T}^{p}>100 Mev");
                t3b->SetNDC();
                t3b->SetTextFont(12);
                t3b->SetTextSize(0.04);
                t3b->SetTextAlign(20);
                
                
TLatex *t4b = new TLatex(0.58,0.45,"#theta_{p}<13 mrad");
                t4b->SetNDC();
                t4b->SetTextFont(12);
                t4b->SetTextSize(0.04);
                t4b->SetTextAlign(20);
                
                
TLatex *t5b = new TLatex(0.65,0.39,"p_{T}^{#mu}>300 MeV & |#eta_{#mu}|<3.5");
                t5b->SetNDC();
                t5b->SetTextFont(12);
                t5b->SetTextSize(0.04);
                t5b->SetTextAlign(20);
                


// =======================================================================



TCanvas* c1 = new TCanvas("c1","Massdilepton", 10, 10, 900, 700);

//histMassdilepton->SetTitle("Jet Algorithem = ee_genkt_cambridge");
histMassdilepton->GetXaxis()->SetTitle("M_{#mu^{+}#mu^{-}} [GeV]");
//histMassdilepton->GetXaxis()->SetTitleOffset(1.25);
histMassdilepton->GetXaxis()->SetLabelFont(22);
histMassdilepton->GetXaxis()->SetTitleFont(22);
histMassdilepton->GetYaxis()->SetTitle("# Events");
histMassdilepton->GetYaxis()->SetTitleOffset(1.40);
histMassdilepton->GetYaxis()->SetLabelFont(22);
histMassdilepton->GetYaxis()->SetTitleFont(22);

// histMassdilepton->GetYaxis()->SetRangeUser(0,140);

cout<<"Integral(Massdilepton) =" << histMassdilepton->Integral()/4.0<<endl;

   // histMassdilepton->SetFillStyle(3001); 
//    histMassdilepton->SetFillColor(kGreen+1);
    histMassdilepton->SetLineWidth(3);
    histMassdilepton->SetLineColor(kBlue+1);
    
    histMassdilepton->Draw("hist");
    
    
//     c1->SetLogy(1);
//   c1->SetLogx(1);

 leg->Draw("same");
 t2a->Draw("same");
// t3a->Draw("same");
// t4a->Draw("same"); 
// t5a->Draw("same");
// t6a->Draw("same");  
// t2b->Draw("same");   
// t3b->Draw("same");    
// t4b->Draw("same");    
// t5b->Draw("same");   
 
c1->SaveAs("Massdilepton.pdf");
//c1->SaveAs("Massdilepton.C");
//c1->SaveAs("Massdilepton.eps");
//c1->SaveAs("Massdilepton.root");
//c1->SaveAs("Massdilepton.jpg");
  


// =======================================================================



TCanvas* c2 = new TCanvas("c2","Ptdilepton", 10, 10, 900, 700);

//histPtdilepton->SetTitle("Jet Algorithem = ee_genkt_cambridge");
histPtdilepton->GetXaxis()->SetTitle("P_{T}^{#mu^{+}#mu^{-}} [GeV]");
//histPtdilepton->GetXaxis()->SetTitleOffset(1.25);
histPtdilepton->GetXaxis()->SetLabelFont(22);
histPtdilepton->GetXaxis()->SetTitleFont(22);
histPtdilepton->GetYaxis()->SetTitle("# Events");
histPtdilepton->GetYaxis()->SetTitleOffset(1.40);
histPtdilepton->GetYaxis()->SetLabelFont(22);
histPtdilepton->GetYaxis()->SetTitleFont(22);

//histPtdilepton->GetYaxis()->SetRangeUser(0,100);

cout<<"Integral(Ptdilepton) ="<<histPtdilepton->Integral()/(30.0/10.0)<<endl;

   // histPtdilepton->SetFillStyle(3001); 
//    histPtdilepton->SetFillColor(kGreen+1);
    histPtdilepton->SetLineWidth(3);
    histPtdilepton->SetLineColor(kBlue+1);
    
    histPtdilepton->Draw("hist");

 leg->Draw("same");
 t2a->Draw("same");
// t3a->Draw("same");
// t4a->Draw("same"); 
// t5a->Draw("same");
// t6a->Draw("same");  
// t2b->Draw("same");   
// t3b->Draw("same");    
// t4b->Draw("same");    
// t5b->Draw("same");   

c2->SaveAs("Ptdilepton.pdf");
//c2->SaveAs("Ptdilepton.C");
//c2->SaveAs("Ptdilepton.eps");
//c2->SaveAs("Ptdilepton.root");
//c2->SaveAs("Ptdilepton.jpg");
  

// =======================================================================



TCanvas* c3 = new TCanvas("c3","etall", 10, 10, 900, 700);

//histetall->SetTitle("Jet Algorithem = ee_genkt_cambridge"); t5a->Draw("same");
histetall->GetXaxis()->SetTitle("#eta^{#mu^{+}#mu^{-}}");
//histetall->GetXaxis()->SetTitleOffset(1.25);
histetall->GetXaxis()->SetLabelFont(22);
histetall->GetXaxis()->SetTitleFont(22);
histetall->GetYaxis()->SetTitle("# Events");
histetall->GetYaxis()->SetTitleOffset(1.40);
histetall->GetYaxis()->SetLabelFont(22);
histetall->GetYaxis()->SetTitleFont(22);

//histetall->GetYaxis()->SetRangeUser(1,100);


 cout<<"Integral(etal) ="<<histetall->Integral()<<endl;

   // histetall->SetFillStyle(3001);
//    histetall->SetFillColor(kGreen+1);
    histetall->SetLineWidth(3);
    histetall->SetLineColor(kBlue+1);

//    histetall->Draw("hist");
    histetall->Draw("hist");


 leg->Draw("same");
 t2a->Draw("same");
// t3a->Draw("same");
// t4a->Draw("same");
// t5a->Draw("same");
// t6a->Draw("same");
// t2b->Draw("same");
// t3b->Draw("same");
// t4b->Draw("same");
// t5b->Draw("same");

// c3->SetLogy(1);


c3->SaveAs("NPART-6-etal.pdf");
//c3->SaveAs("etal.C");
//c3->SaveAs("etal.eps");
//c3->SaveAs("etal.root");
//c3->SaveAs("etal.jpg");




// =======================================================================



TCanvas* c4 = new TCanvas("c4","Yll", 10, 10, 900, 700);

//histYll->SetTitle("Jet Algorithem = ee_genkt_cambridge"); t5a->Draw("same");
histYll->GetXaxis()->SetTitle("Y^{#mu^{+}#mu^{-}}");
//histYll->GetXaxis()->SetTitleOffset(1.25);
histYll->GetXaxis()->SetLabelFont(22);
histYll->GetXaxis()->SetTitleFont(22);
histYll->GetYaxis()->SetTitle("# Events");
histYll->GetYaxis()->SetTitleOffset(1.40);
histYll->GetYaxis()->SetLabelFont(22);
histYll->GetYaxis()->SetTitleFont(22);

//histYll->GetYaxis()->SetRangeUser(1,100);


 cout<<"Integral(Yl) ="<<histYll->Integral()<<endl;

   // histYll->SetFillStyle(3001);
//    histYll->SetFillColor(kGreen+1);
    histYll->SetLineWidth(3);
    histYll->SetLineColor(kBlue+1);

//    histYll->Draw("hist");
    histYll->Draw("hist");


 leg->Draw("same");
 t2a->Draw("same");
// t3a->Draw("same");
// t4a->Draw("same");
// t5a->Draw("same");
// t6a->Draw("same");
// t2b->Draw("same");
// t3b->Draw("same");
// t4b->Draw("same");
// t5b->Draw("same");

// c4->SetLogy(1);


c4->SaveAs("NPART-6-Yll.pdf");
//c4->SaveAs("Yll.C");
//c4->SaveAs("Yll.eps");
//c4->SaveAs("Yll.root");
//c4->SaveAs("Yll.jpg");




// =======================================================================



TCanvas* c5 = new TCanvas("c5","Thetall", 10, 10, 900, 700);

//histThetall->SetTitle("Jet Algorithem = ee_genkt_cambridge"); t5a->Draw("same");
histThetall->GetXaxis()->SetTitle("#theta^{#mu^{+}#mu^{-}}");
//histThetall->GetXaxis()->SetTitleOffset(1.25);
histThetall->GetXaxis()->SetLabelFont(22);
histThetall->GetXaxis()->SetTitleFont(22);
histThetall->GetYaxis()->SetTitle("# Events");
histThetall->GetYaxis()->SetTitleOffset(1.40);
histThetall->GetYaxis()->SetLabelFont(22);
histThetall->GetYaxis()->SetTitleFont(22);

//histThetall->GetYaxis()->SetRangeUser(1,100);


 cout<<"Integral(Yl) ="<<histThetall->Integral()<<endl;

   // histThetall->SetFillStyle(3001);
//    histThetall->SetFillColor(kGreen+1);
    histThetall->SetLineWidth(3);
    histThetall->SetLineColor(kBlue+1);

//    histThetall->Draw("hist");
    histThetall->Draw("hist");


 leg->Draw("same");
 t2a->Draw("same");
// t3a->Draw("same");
// t4a->Draw("same");
// t5a->Draw("same");
// t6a->Draw("same");
// t2b->Draw("same");
// t3b->Draw("same");
// t4b->Draw("same");
// t5b->Draw("same");

// c5->SetLogy(1);


c5->SaveAs("NPART-6-Thetall.pdf");
//c5->SaveAs("Thetall.C");
//c5->SaveAs("Thetall.eps");
//c5->SaveAs("Thetall.root");
//c5->SaveAs("Thetall.jpg");


}



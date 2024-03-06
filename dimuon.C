//
// ***************************** exclusive production of dimuons ******************************
//

#define dimuon_cxx

#include "dimuon.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


TFile *target;
TTree *Tsignal_LHeC = new TTree("LHeC_dimuon","LHeC_dimuon");
TFile *F;


// **********************************************************************   
// Book Histograms 
// **********************************************************************   

    TH1 *histMassdilepton  =  new TH1F("M_{inv}", "",   30, 0.0, 10.0);
    TH1 *histPtdilepton    =  new TH1F("Ptll", "",      30, 0.0, 10.0);
    TH1 *histetall         =  new TH1F("etall", "",     30, -5.0, 5.0); 


    TLorentzVector lepton1;      
    TLorentzVector lepton2;    

    TLorentzVector MydiLepton; 


    Float_t Mll   = 0.0;
    Float_t Ptll  = 0.0;
    Float_t Etall = 0.0;
    

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


    Tsignal_LHeC->Branch("Mll",&Mll);
    Tsignal_LHeC->Branch("Ptll",&Ptll);
    Tsignal_LHeC->Branch("Etall",&Etall);


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
        

  lepton1.SetPtEtaPhiE( pt[5], eta[5], phi[5], E[5] );
  lepton2.SetPtEtaPhiE( pt[7], eta[7], phi[7], E[7] );


  MydiLepton = lepton1 + lepton2;  
  
/*

  Mll   =  lepton1.M()   + lepton2.M();
  Ptll  =  lepton1.Pt()  + lepton2.Pt();
  Etall =  lepton1.Eta() + lepton2.Eta();

*/


    Mll   =  MydiLepton.M();
    Ptll  =  MydiLepton.Pt();
    Etall =  MydiLepton.Eta();


//  cout << " Mll   = "  << Mll << endl;
//  cout << " Ptll  = "  << Ptll << endl;
//  cout << " Etall = "  << Etall << endl;


    histMassdilepton->Fill(Mll);      
    histPtdilepton->Fill(Ptll);
    histetall->Fill(Etall);

      
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
histetall->GetXaxis()->SetTitle("#eta^{l}");
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



}



#ifndef Test_TreeInfo_h
#define Test_TreeInfo_h

#include <Math/Vector3D.h>
#include <Math/Vector4D.h>
#include <TFile.h>
#include <TTree.h>

#include <string>

namespace lpair {
  struct TreeRun {
    double sqrt_s;
    double xsect, errxsect;
    unsigned int num_events, litigious_events;
    TTree* tree;

    TreeRun() : tree(NULL) { clear(); }
    void clear() {
      sqrt_s = -1.;
      xsect = errxsect = -1.;
      num_events = litigious_events = 0;
    }
    void create() {
      tree = new TTree("run", "a tree containing information on the previous run");
      if (!tree)
        return;
      tree->Branch("xsect", &xsect, "xsect/D");
      tree->Branch("errxsect", &errxsect, "errxsect/D");
      tree->Branch("num_events", &num_events, "num_events/i");
      tree->Branch("litigious_events", &litigious_events, "litigious_events/i");
      tree->Branch("sqrt_s", &sqrt_s, "sqrt_s/D");
    }
    void fill() { tree->Fill(); }
    void attach(const char* filename) { attach(TFile::Open(filename)); }
    void attach(TFile* file) {
      tree = dynamic_cast<TTree*>(file->Get("run"));
      if (!tree)
        return;
      tree->SetBranchAddress("xsect", &xsect);
      tree->SetBranchAddress("errxsect", &errxsect);
      tree->SetBranchAddress("num_events", &num_events);
      tree->SetBranchAddress("litigious_events", &litigious_events);
      tree->SetBranchAddress("sqrt_s", &sqrt_s);
      if (tree->GetEntriesFast() > 1)
        std::cerr << "The run tree has more than one entry." << std::endl;
      tree->GetEntry(0);
    }
  };

  struct TreeEvent {
    // book a sufficienly large number to allow the large multiplicity
    // of excited proton fragmentation products
    static const unsigned short maxpart = 5000;

    TTree* tree;

    float gen_time, tot_time;
    int nremn_ch[2], nremn_nt[2], np;
    std::vector<ROOT::Math::XYZTVector> momentum, *pMom;
    double pt[maxpart], eta[maxpart], phi[maxpart], rapidity[maxpart];
    double E[maxpart], m[maxpart], charge[maxpart];
    int pdg_id[maxpart], parent1[maxpart], parent2[maxpart];
    int stable[maxpart], role[maxpart], status[maxpart];

    TreeEvent() : tree(nullptr), pMom(nullptr) { clear(); }

    void clear() {
      gen_time = tot_time = 0.;
      for (unsigned short i = 0; i < 2; ++i)
        nremn_ch[i] = nremn_nt[i] = 0;
      np = 0;
      momentum.clear();
      for (unsigned short i = 0; i < maxpart; ++i) {
        pt[i] = eta[i] = phi[i] = rapidity[i] = E[i] = m[i] = charge[i] = 0.;
        pdg_id[i] = parent1[i] = parent2[i] = stable[i] = role[i] = status[i] = 0;
      }
    }
    void fill() {
      if (!tree)
        throw std::runtime_error("TreeEvent: Trying to fill a non-existent tree!");

      tree->Fill();
      clear();
    }
    void create(TTree* t) {
      tree = t;
      if (!tree)
        return;
      tree->Branch("npart", &np, "npart/I");
      tree->Branch("nremn_charged", nremn_ch, "nremn_charged[2]/I");
      tree->Branch("nremn_neutral", nremn_nt, "nremn_neutral[2]/I");
      tree->Branch("role", role, "role[npart]/I");
      pMom = &momentum;
      tree->Branch("momentum", "std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > >", &pMom);
      tree->Branch("pt", pt, "pt[npart]/D");
      tree->Branch("eta", eta, "eta[npart]/D");
      tree->Branch("phi", phi, "phi[npart]/D");
      tree->Branch("rapidity", rapidity, "rapidity[npart]/D");
      tree->Branch("E", E, "E[npart]/D");
      tree->Branch("m", m, "m[npart]/D");
      tree->Branch("charge", charge, "charge[npart]/D");
      tree->Branch("pdg_id", pdg_id, "pdg_id[npart]/I");
      tree->Branch("parent1", parent1, "parent1[npart]/I");
      tree->Branch("parent2", parent2, "parent2[npart]/I");
      tree->Branch("stable", stable, "stable[npart]/I");
      tree->Branch("status", status, "status[npart]/I");
      tree->Branch("generation_time", &gen_time, "generation_time/F");
      tree->Branch("total_time", &tot_time, "total_time/F");
    }
    void attach(TFile* f, const std::string& tree_name = "events") {
      tree = dynamic_cast<TTree*>(f->Get(tree_name.c_str()));
      attach(tree);
    }
    void attach(TTree* t) {
      tree = t;
      if (!tree)
        return;
      tree->SetBranchAddress("npart", &np);
      tree->SetBranchAddress("nremn_charged", nremn_ch);
      tree->SetBranchAddress("nremn_neutral", nremn_ch);
      tree->SetBranchAddress("role", role);
      tree->SetBranchAddress("momentum", &pMom);
      tree->SetBranchAddress("pt", pt);
      tree->SetBranchAddress("eta", eta);
      tree->SetBranchAddress("phi", phi);
      tree->SetBranchAddress("rapidity", rapidity);
      tree->SetBranchAddress("E", E);
      tree->SetBranchAddress("m", m);
      tree->SetBranchAddress("charge", charge);
      tree->SetBranchAddress("pdg_id", pdg_id);
      tree->SetBranchAddress("parent1", parent1);
      tree->SetBranchAddress("parent2", parent2);
      tree->SetBranchAddress("stable", stable);
      tree->SetBranchAddress("status", status);
      tree->SetBranchAddress("generation_time", &gen_time);
      tree->SetBranchAddress("total_time", &tot_time);
    }
  };
}  // namespace lpair

#endif

//
//  PersonProfile.hpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include <stdio.h>
#include <set>
#include "utilities.h"
#include "provided.h"
#include "RadixTree.h"


using namespace std;

class PersonProfile {
public:
    PersonProfile(string name, string email);
    ~PersonProfile();
    string GetName() const;
    string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    string m_name;
    string m_email;
    set<AttValPair*> m_attributes;
    RadixTree<string>* person_tree;
    int num_pairs;
};

#endif /* PersonProfile_hpp */

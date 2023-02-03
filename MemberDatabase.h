//
//  MemberDatabase.hpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "provided.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include "AttributeTranslator.h" 

using namespace std;

class MemberDatabase {
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(string filename);
    vector<string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(string email) const;
private:
    RadixTree<PersonProfile*> member_tree;
    RadixTree<vector<string>> m_emailsToKeys;
    vector<PersonProfile*> m_people;
};
#endif /* MemberDatabase_hpp */

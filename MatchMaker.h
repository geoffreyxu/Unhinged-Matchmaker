//
//  MatchMaker.hpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include <stdio.h>
#include <iostream>
#include <set>
#include <unordered_map>
#include "utilities.h"
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "RadixTree.h"



using namespace std;

class MatchMaker {
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    vector<EmailCount> IdentifyRankedMatches(string email, int threshold) const;
private:
    const MemberDatabase* m_members;
    const AttributeTranslator* m_translator;
};

#endif /* MatchMaker_hpp */

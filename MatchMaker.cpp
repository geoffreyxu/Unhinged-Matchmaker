//
//  MatchMaker.cpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_members = &mdb;
    m_translator = &at;
}

MatchMaker::~MatchMaker()
{
}

vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
    vector<AttValPair> inputPairs;
    vector<AttValPair> compatiblePairs;
    AttValPair attval;
    const PersonProfile* newPerson = m_members->GetMemberByEmail(email);
    for (int i = 0; i < newPerson->GetNumAttValPairs(); i++)
    {
        newPerson->GetAttVal(i, attval);
        inputPairs.push_back(attval);
    }
    for (int i = 0; i < inputPairs.size(); i++)
    {
        vector<AttValPair> hold = m_translator->FindCompatibleAttValPairs(inputPairs[i]);
        compatiblePairs.insert(compatiblePairs.end(), hold.begin(), hold.end());
    }
    set<AttValPair> setPairs;
    for (int i = 0; i < compatiblePairs.size(); i++)
    {
        setPairs.insert(compatiblePairs[i]);
    }
    //set<AttValPair> setPairs(compatiblePairs.begin(), compatiblePairs.end());
    unordered_map<string, int> countCompatibles;
    set<AttValPair>::iterator it = setPairs.begin();
    while (it != setPairs.end())
    {
        vector<string> place = m_members->FindMatchingMembers(*it);
        for (int i = 0; i < place.size(); i++)
        {
            if (countCompatibles.find(place[i]) != countCompatibles.end())
            {
                countCompatibles.at(place[i])++;
 
            }
            else
            {
                pair<string, int> toInsert(place[i], 1);
                countCompatibles.insert(toInsert);
            }
        }
        it++;
    }
    vector<EmailCount> v;
    unordered_map<string, int>::iterator itr = countCompatibles.begin();
    while (itr != countCompatibles.end())
    {
        if (itr->second >= threshold)
        {
            if (v.empty())
                v.push_back(EmailCount(itr->first, itr->second));
            else if (itr->second < v.back().count)
                v.push_back(EmailCount(itr->first, itr->second));
            else if (itr->second == v.back().count && itr->first > v.back().email)
                v.push_back(EmailCount(itr->first, itr->second));
            else
            {
                vector<EmailCount>::iterator iter = v.begin();
                while (iter != v.end() && itr->second < (*iter).count)
                {
                    iter++;
                }
                if (itr->second == (*iter).count)
                {
                    while (iter != v.end() && itr->first > (*iter).email && itr->second == (*iter).count)
                        iter++;
                }
                v.insert(iter, EmailCount(itr->first, itr->second));
                
            }
        }
        itr++;
    }
    return v;
}

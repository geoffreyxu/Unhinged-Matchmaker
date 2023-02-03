//
//  PersonProfile.cpp
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#include "PersonProfile.h"

PersonProfile::PersonProfile(string name, string email) : m_name(name), m_email(email), num_pairs(0)
{
    person_tree = new RadixTree<string>;
}

PersonProfile::~PersonProfile()
{
    while (!m_attributes.empty())
    {
        set<AttValPair*>::iterator it = m_attributes.begin();
        m_attributes.erase(it);
        delete *it;
    }
    delete person_tree;
}

string PersonProfile::GetName() const
{
    return m_name;
}

string PersonProfile::GetEmail() const
{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair &attval)
{
    person_tree->insert(attval.attribute, attval.value);
    string temp1 = attval.attribute;
    string temp2 = attval.value;
    m_attributes.insert(new AttValPair(temp1,temp2));
    num_pairs++;
}

int PersonProfile::GetNumAttValPairs() const
{
    return num_pairs;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair &attval) const
{
    set<AttValPair*>::iterator it = m_attributes.begin();
    int count = 0;
    while (it != m_attributes.end())
    {
        if (count == attribute_num)
        {
            attval.attribute = (*it)->attribute;
            attval.value = (*it)->value;
            return true;
        }
        count++;
        it++;
    }
    return false;
}




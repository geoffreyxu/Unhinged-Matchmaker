//
//  AttributeTranslator.h
//  unhingedp4
//
//  Created by Geoffrey  Xu on 3/3/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <fstream>
#include <istream>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <functional>
#include "provided.h"
#include "RadixTree.h"

using namespace std;

class AttributeTranslator {
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(string filename);
    vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<vector<AttValPair>> m_compatibles;
    // unordered_set<vector<AttValPair>*> attributeValues;
    // RadixTree<unordered_set<string>> m_compatibles;
};

#endif /* AttributeTranslator_h */

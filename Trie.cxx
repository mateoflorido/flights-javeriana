//
// Created by mateo on 12/09/18.
//

#include "Trie.h"
#include <bits/stdc++.h>

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


FJA::Trie *FJA::Trie::getNode(void) {
    Trie *p = new Trie;
    p->isWordEnd = false;
    for (auto i = 0; i < 26; i++)
        p->Desc[i] = nullptr;
    return p;
}

void FJA::Trie::Insert(FJA::Trie *root, const std::string key) {
    Trie *pCrawl = root;
    for (auto level = 0; level < key.length(); level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->Desc[index])
            pCrawl->Desc[index] = getNode();
        pCrawl = pCrawl->Desc[index];
    }
}

bool FJA::Trie::Search(FJA::Trie *root, const std::string key) {
    int length = key.length();
    Trie *pCrawl = root;
    for (auto level = 0; level < length; level++) {
        int index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->Desc[index])
            return false;
        pCrawl = pCrawl->Desc[index];
    }
    return (pCrawl != nullptr && pCrawl->isWordEnd);
}

bool FJA::Trie::IsLastNode(FJA::Trie *root) {
    for (auto i = 0; i < 26; i++)
        if (root->Desc[i])
            return 0;
    return 1;
}
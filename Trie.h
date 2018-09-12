//
// Created by mateo on 12/09/18.
//

#ifndef FLIGHTS_JAVERIANA_TRIE_H
#define FLIGHTS_JAVERIANA_TRIE_H

#include <string>

namespace FJA {
    class Trie {
    public:
        /**
         * @brief
         * @return
         */
        Trie *getNode(void);

        /**
         * @brief
         * @param root
         * @param key
         */
        void Insert(Trie *root, const std::string key);

        /**
         * @brief
         * @param root
         * @param key
         * @return
         */
        bool Search(Trie *root, const std::string key);

        /**
         * @brief
         * @param root
         * @return
         */
        bool IsLastNode(Trie *root);




    protected:
        Trie *Desc[26];
        bool isWordEnd;
    };
}


#endif //FLIGHTS_JAVERIANA_TRIE_H

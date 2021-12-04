#include <vector>
#include <string>
#include <random>
#include <iostream>

// random seeds
std::random_device    r;
std::mt19937        gen(r());

// generates a random sequence of n cards
std::string genCardSeq(int n, bool joker = false)
{
    std::string cardSequence = "";

    std::vector<std::string> suits = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    std::vector<std::string> ranks = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "JACK", "QUEEN", "KING"};

    // uniform random number generators
    std::uniform_int_distribution<int> u1(0, 3);
    std::uniform_int_distribution<int> u2(0, 11);

    // random position for the joker card in the sequence (when joker=true)
    std::uniform_int_distribution<int> u3(0, n-1);
    int jokerPos = u3(gen);

    std::string nextCard;

    for(int i = 0; i < n; i++)
    {
        nextCard = joker && jokerPos==i ? "JOKER" : suits[u1(gen)] + "#" + ranks[u2(gen)];

        cardSequence += nextCard;

        if(i == n - 1)
            continue;

        cardSequence += " ";
    }

    return cardSequence;
}

void play(std::string computer, std::string player){
    int pos = computer.find(player);

    if(pos == std::string::npos){
        std::cout << "LOSS" << std::endl;
        return;
    }
    std::cout << "WIN ";
    while (pos != std::string::npos){
        int card_pos = 0;
        for (int i = 0; i < pos; i++){
            if (computer[i] == ' '){
                card_pos++;
            }
        }
        std::cout << card_pos << " ";
        pos = computer.find(player, pos + 1);
    }
    std::cout << std::endl;
}

void test1() // simple test
{
    std::string computer = "CLUBS#ACE CLUBS#ACE CLUBS#ACE HEARTS#JACK SPADES#9 SPADES#9 HEARTS#JACK SPADES#9";

    std::string player = "HEARTS#JACK SPADES#9";
    play(computer, player);
}

void test2() // random test
{
    int n = 50;
    int m = 8;

    std::string computer = genCardSeq(n);
    std::string player = genCardSeq(m);

    std::cout << computer << std::endl;
    std::cout << std::endl;
    std::cout << player << std::endl;

    play(computer, player);


}

void test3() // for those who want the bonus points
{
    int n = 10;
    int m = 5;

    std::string computer = genCardSeq(n);
    std::string player = genCardSeq(m, true); // include the joker in the generation :o)

    std::cout << computer << std::endl;
    std::cout << std::endl;
    std::cout << player << std::endl;

    play(computer, player);

}


int main()
{
    test1();
    test2();
    //test3();

    return 0;
}

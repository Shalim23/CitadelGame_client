#pragma once
//
//struct RulesData
//{
//    const char* header = nullptr;
//    const char* contents = nullptr;
//};
//
//const static std::vector<const char*> GameRulesCategoriesNames(
//    {"General Rules",
//    "Characters",
//    "Districts"}
//);
//);
//
////General rules
//
//const static char* IntroductionHeader("Introduction");
//const static char* DistrictCardsHeader("District Cards");
//const static char* CharactersHeader("Characters");
//const static char* PlayingTheGameHeader("Playing the Game");
//const static char* GameEndHeader("Game End");
//const static char* OtherRulesHeader("Other Rules");
//
//const static char* IntroductionContetns(
//    "In Citadels, each player leads a city and seeks to increase its prosperity by building new city districts. "
//    "The game ends after one player has built his eighth district, after which a winner is determined by how many points his completed city is worth. "
//    "Building the most impressive city, however, is not an easy task. "
//    "Only by influencing nobles, merchants, and other powerful characters of the realm will you achieve success. "
//);
//const static char* DistrictCardsContetns(
//    "These cards represent the various districts that you can add to your city. "
//    "Each district card has a cost, represented by a number of gold coins along the card’s left edge. "
//    "In order to put a district card into play, you must pay its cost in gold. "
//    "Each district card also exhibits a colored circle on its bottom left - hand corner, which tells you what type of district it is: "
//    "Yellow - King’s income, Blue - Bishop’s income, Green - Merchant’s income, Red - Warlord’s income, Purple - special benefits described on the card itself. "
//);
//const static char* CharactersContetns(
//    "These cards represent the characters that players seek to influence during every game round. "
//    "There are eight basic characters in Citadels. "
//    "In addition to a special ability, each character card has a rank number between one and eight. "
//    "This number is printed on the upper left - hand side of the card. "
//    "Every character in Citadels has a unique special power. "
//    "You may use your character’s power once at any point during your turn. "
//    "However, you are never required to use a special power should you choose not to. "
//    "Each character’s power is summarized on its card. "
//);
//const static char* PlayingTheGameContetns(
//    "Playing the game with 4–6 players is described below. "
//    "In the beginning of the round 2 random character cards are removed - one is secretly and one in the open. "
//    "Each player secretly chooses a character, starting from the player who currently possesses the Crown. "
//    "After the last player has chosen, remaining unchosen cards are secretly removed. "
//    "Once all players have chosen a character card, each character is called one-at-a-time in the order of numerical rank. "
//    "In this way, the first called out is the “Assassin” (#1), then the “Thief” (#2), etc. "
//    "If character is not revealed - next character is called in rank order. "
//    "When the name of your character card is called - take your turn. "
//    "When your turn is over, play proceeds to every character in order of their rank number, giving all players one turn(unless murdered by the Assassin, see Assassin's card description). "
//    "On your turn, you must first take an action, after which you may build a district card. "
//    "At the beginning of your turn, you must do one of the following: take two gold from the bank or draw two district cards from the District Deck, choose one card to put in your hand, and place the other card on the bottom of the District Deck. "
//    "After you have taken an action, you may build one district card in your city(that is, play it from your hand. "
//    "In order to do so, you must pay the cost of the district, in gold, to the bank. You may choose not to build a district card if you wish. "
//    "The gold cost of building a district card is equal to the number of gold coins on the upper left - hand side of the card. "
//    "You may not build a district such that you have two identical districts(two “Castle” cards, two “Market” cards, etc.) in your city. "
//    "Each character has a special ability, also called its power. You may use your character’s power once during your turn. "
//    "Each character’s special power is summarized on its respective card and explained in detail on the other page. "
//    "After all the characters have been called, Character Deck is shuffled and a new round begins. "
//);
//
//const static char* GameEndContetns(
//    "When a player builds his eighth district, the game ends after the current round is completed. "
//    "Scoring process is following: "
//    "1. A player receives a number of points equal to the total combined gold cost of all the district cards in his city at the end of the game. "
//    "2. If a player has at least one district in each of the five colors, he receives three points. "
//    "3. If a player was the first player to build eight districts, he receives four points. "
//    "4. All other players who have managed to build eight districts at the end of the game receive two points. "
//    "The winner of the game is the player with the most points. "
//    "In the case of a tie, only total points from step 1 are compared. "
//    "If there is still a tie, the player with the most gold wins. "
//);
//
//const static char* OtherRulesContetns(
//    "A few more rules are explained below, including special modifications for games with two, three and seven players. "
//    "In a two- or three-player game, all players play with two characters each. The game is played normally, except that each player has two turns each round (one turn for each character). "
//    "If you are playing with two or three players, the rules for preparing the Character Deck and choosing character cards are changed in the following ways: "
//    "Two-player Game. "
//    "1. The player who has the Crown marker (Player A) secretly selects a character card from the remaining cards. "
//    "2. Player B selects one card for himself and then chooses another character to remove from the deck. "
//    "3. Player A selects one of character cards for himself, and then he chooses another character to remove from the deck. "
//    "4. Player B takes one of the remaining character cards for himself. "
//    "The Three - player Game. "
//    "The player with the Crown secretly chooses a character for himself."
//    "Next player also chooses a card for himself."
//    "This continues until each player has chosen two cards from the Character Deck."
//    "The last player selects one card for himself."
//    "The Seven - player Game. "
//    "A seven - player game of Citadels plays much like the normal game, with one exception: "
//    "During the “Choose Characters” step of a seven - player game, the seventh player also looks at the removed card."
//    "He then chooses one of these two cards, secretly removing the rest."
//);
//
//const static std::vector<RulesData> GameRulesDataArray({
//    RulesData{IntroductionHeader, IntroductionContetns},
//    RulesData{DistrictCardsHeader, DistrictCardsContetns},
//    RulesData{CharactersHeader, CharactersContetns},
//    RulesData{PlayingTheGameHeader, PlayingTheGameContetns},
//    RulesData{GameEndHeader, GameEndContetns},
//    RulesData{OtherRulesHeader, OtherRulesContetns},
//    });
//
//
////Characters
//
//const static char* AssassinHeader("Assassin");
//const static char* ThiefHeader("Thief");
//const static char* MagicianHeader("Magician");
//const static char* KingHeader("King");
//const static char* BishopHeader("Bishop");
//const static char* MerchantHeader("Merchant");
//const static char* ArchitectHeader("Architect");
//const static char* WarlordHeader("Warlord");
//
//const static char* AssassinContetns(
//    "Select the character that you wish to murder. "
//    "The murdered character misses his entire turn. "
//);
//
//const static char* ThiefContetns(
//    "Select the character from whom you wish to steal. "
//    "When the player who has that character is called upon to take his turn, you first take all of his gold. "
//    "You may not steal from the Assassin or the Assassin’s target. "
//);
//
//const static char* MagicianContetns(
//    "At any time during your turn, you have one of two options: "
//    "1. Exchange your entire hand of cards with the hand of another player(this applies even if you have no cards in your hand, in which case you simply take the other player’s cards). "
//    "2. Select any number of cards from your hand facedown and change them on equal number of cards from the District Deck. "
//);
//
//const static char* KingContetns(
//    "You receive one gold for each noble (yellow) district in your city. "
//    "When the King is called, you immediately receive the Crown. "
//    "You now will be the first player to choose your character during the next round. "
//    "If there is no King during the next round, you keep the Crown. "
//    "If you are murdered, you skip your turn like any other character. "
//    "Nevertheless, after the last player has played his turn, when it becomes known that you had the murdered King’s character card, you take the Crown(as the King’s heir). "
//);
//
//const static char* BishopContetns(
//    "You receive one gold for each religious (blue) district in your city. "
//    "Your districts may not be destroyed by the Warlord. "
//);
//
//const static char* MerchantContetns(
//    "You receive one gold for each trade (green) district in your city. "
//    "After you take an action, you receive one additional gold. "
//);
//
//const static char* ArchitectContetns(
//    "After you take an action, you draw two additional district cards and put both in your hand. "
//    "You may build up to three districts during your turn. "
//);
//
//const static char* WarlordContetns(
//    "You receive one gold for each military (red) district in your city. "
//    "At the end of your turn, you may destroy one district of your choice by paying a number of gold equal to one less than the cost of the district. "
//    "Thus, you may destroy a cost one district for free, a cost two district for one gold, or a cost six district for five gold, etc. "
//    "You may destroy one of your own districts." 
//    "You may not, however, destroy a district in a city that is already completed by having eight districts. "
//);
//
//const static std::vector<RulesData> CharactersRulesDataArray({
//    RulesData{AssassinHeader, AssassinContetns},
//    RulesData{ThiefHeader, ThiefContetns},
//    RulesData{MagicianHeader, MagicianContetns},
//    RulesData{KingHeader, KingContetns},
//    RulesData{BishopHeader, BishopContetns},
//    RulesData{MerchantHeader, MerchantContetns},
//    RulesData{ArchitectHeader, ArchitectContetns},
//    RulesData{WarlordHeader, WarlordContetns},
//    });
//
//
////Special districts
//
//const static char* CemeteryHeader("Cemetery");
//const static char* FortHeader("Fort");
//const static char* UniversityHeader("University");
//const static char* DragonGateHeader("Dragon Gate");
//const static char* SchoolOfMagicHeader("School of Magic");
//const static char* LaboratoryHeader("Laboratory");
//const static char* ObservatoryHeader("Observatory");
//const static char* BlacksmithHeader("Blacksmith");
//const static char* TheGreatWallHeader("The Great Wall");
//const static char* GhostTownHeader("Ghost Town");
//const static char* LibraryHeader("Library");
//
//
//const static char* CemeteryContetns(
//    "When the Warlord destroys the district of the player in whose city the Cemetery is built, the player can pay 1 gold to pick up the card of the destroyed distric in his hand. "
//    "A player cannot do this if he was a Warlord. "
//);
//
//const static char* FortContetns(
//    "The Warlord cannot destroy the Fort."
//);
//
//const static char* UniversityContetns(
//    "Gives 2 additional points in the end of the game. "
//);
//
//const static char* DragonGateContetns(
//    "Gives 2 additional points in the end of the game. "
//);
//
//const static char* SchoolOfMagicContetns(
//    "During the calculation of income per turn, the School of Magic can be a district of any color at the player’s choice. "
//    "For example, if in the current round the player is the King, the School of Magic can be counted as a yellow (noble) district. "
//);
//const static char* LaboratoryContetns(
//    "Once per turn a player has the right to get rid of 1 district card from his hand and get 1 gold from the bank. "
//);
//
//const static char* ObservatoryContetns(
//    "If the player decides to take distric cards from the deck on his turn, he draws 3 cards and chooses one of them. "
//);
//
//const static char* BlacksmithContetns(
//    "Once per turn, the player has the opportunity to pay 2 gold for the right to receive 3 district cards. "
//);
//
//const static char* TheGreatWallContetns(
//    "In order to destroy one of the districts of the player who built the Great Wall in his city, the Warlord will have to pay full price of the district. "
//);
//
//const static char* GhostTownContetns(
//    "During the final scoring, the Ghost Town may be a district of any color of the player’s choice. "
//    "This rule is not applied if the district was built in the last round. "
//);
//
//const static char* LibraryContetns(
//    "If during his action a player decides to take district cards from the deck, then he keeps all cards for himself. "
//);
//
//const static std::vector<RulesData> DistrictRulesDataArray({
//    RulesData{CemeteryHeader, CemeteryContetns},
//    RulesData{FortHeader, FortContetns},
//    RulesData{UniversityHeader, UniversityContetns},
//    RulesData{DragonGateHeader, DragonGateContetns},
//    RulesData{SchoolOfMagicHeader, SchoolOfMagicContetns},
//    RulesData{LaboratoryHeader, LaboratoryContetns},
//    RulesData{ObservatoryHeader, ObservatoryContetns},
//    RulesData{BlacksmithHeader, BlacksmithContetns},
//    RulesData{TheGreatWallHeader, TheGreatWallContetns},
//    RulesData{GhostTownHeader, GhostTownContetns},
//    RulesData{LibraryHeader, LibraryContetns},
//    });
//
//
//const static std::vector<std::vector<RulesData>> RulesDataArray({
//    GameRulesDataArray,
//    CharactersRulesDataArray,
//    DistrictRulesDataArray
// });
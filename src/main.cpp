// C++ File for main

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#include "VariadicToOutputStream.h"

using str_vec_size_type = std::vector<std::string>::size_type;
using pair_vec_size_type = std::vector<std::pair<std::string, int>>::size_type;

const std::vector<std::string> number_words = {
   "zero",
   "one",
   "two",
   "three",
   "four",
   "five",
   "six",
   "seven",
   "eight",
   "nine",
   "ten",
   "eleven",
   "twelve",
   "thirteen",
   "fourteen",
   "fifteen",
   "sixteen",
   "seventeen",
   "eighteen",
   "nineteen",
   "twenty",
   "thirty",
   "forty",
   "fifty",
   "sixty",
   "seventy",
   "eighty",
   "ninety",
   "hundred",
   "thousand",
   "million"
};


long decode_index( int index, const bool& debug=false ) {
   long val = 0;
   if ( index == 30 ) {
      val = 1000000;
   }
   if ( index == 29 ) {
      val = 1000;
   }
   if ( index == 28 ) {
      val = 100;
   }
   if ( ( index <= 27 ) && ( index >= 21 ) ) {
      val = 20 + ( ( index-20 ) * 10 );
   }
   if ( ( index <= 20 ) && ( index >= 0 ) ) {
      val = index;
   }
   return val;
}


std::vector<std::string> reverse_words( std::string words, const bool& debug=false ) {
   std::vector<std::string> words_reversed;
   auto iss = std::istringstream{ words };
   auto str = std::string{};
   
   auto beginning = words_reversed.begin();
   while ( iss >> str ) {
      words_reversed.insert( beginning, str ); 
      beginning = words_reversed.begin();
   }
   debug_cout( debug, __func__, "(): words is '", words, "'" ); 
   
   if ( debug ) {
      std::cout << __func__ << "(): words_reversed is "; 
      std::for_each( words_reversed.begin(), words_reversed.end(), 
         []( std::string const& str ) { std::cout << str << " "; } );
      std::cout << "\n"; 
   }
   return words_reversed;
}


long parse_int( std::string number_string, const bool& debug=false ) {
   long place = 1;
   long val = 0;
   debug_cout( debug, __func__, "(): number_string is '", number_string, "'" ); 

   std::vector<std::string> reversed_number_string = reverse_words( number_string, debug );

   for( str_vec_size_type index = 0; index != reversed_number_string.size(); ++index ) {
      auto str = reversed_number_string.at( index );
      auto find_it = std::find( number_words.begin(), number_words.end(), str );
      int tindex = std::distance( number_words.begin(), find_it ); 
      debug_cout( debug, __func__, "(): str is '", str, "'" ); 
      debug_cout( debug, __func__, "(): str found at ", tindex, ""); 

      long tval = decode_index( tindex, debug );
      debug_cout( debug, __func__, "(): tval is ", tval ); 

      if ( tval > 90 ) {
         debug_cout( debug, __func__, "(): tval > 90. Need to update place" );
         debug_cout( debug, __func__, "(): tval > 90. Place is ", place );
         if ( tval > place ) {
            place = tval;
            debug_cout( debug, __func__, "(): tval > place. tval IS the new place: ", place );
         } else {
            place = place * tval;
            debug_cout( debug, __func__, "(): tval <= place. Multiplying place by tval to get ", place );
         } // end of if ( tval > place ) {
      } else {
         val = val + tval * place;
         debug_cout( debug, __func__, "(): tval < 90. increasing val to ", val );
      } // end of if ( tval > 90 ) {
   } // end of for( vec_size_type index = 0; index != reversed_number_string.size(); ++index ) {

   return val;
}


void usage( const char* prog_name ) {
   std::cout << "Usage: " << prog_name << "\n";
   printf( "\n" );
}


int main( int argc, char** argv ) {
   try {
      std::vector<std::pair<std::string,int>> tests = {
         {"two hundred forty six", 246}, 
         {"three thousand seven hundred five", 3705} 
      };
      bool debug = false;
      for( auto test: tests ) {
         long number = parse_int( test.first, debug );
         std::cout << "Number string is '" << test.first << "\n"; 
         std::cout << "The number is " << number << "\n";
         if ( number != test.second ) {
            std::cout << "Mismatch between expected result: " << test.second 
               << " and actual result: " << number << "\n"; 
         }
      }
      
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
}

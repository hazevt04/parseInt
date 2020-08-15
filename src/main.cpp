// C++ File for main

#include "my_file_io_funcs.h"

void usage( const char* prog_name ) {
   printf( "Usage: %s <num values> <-e/--error>\n", prog_name );
   printf( "\n" );
}

int main( int argc, char** argv ) {
   std::string filename = "foo.bin";
   bool debug = true;
   int num_vals = 10;
   bool inject_error = false;

   std::ostringstream err_msg_stream( std::ostringstream::ate );

   try {
      if ( argc > 2 ) {
         debug_printf( debug, "argv[2] = %s\n", argv[2] ); 
         if ( (!strcmp( argv[2], "-e" )) || (!strcmp( argv[2], "--error" ) ) ) {
            inject_error = true;
         } else {
            err_msg_stream << "Invalid input: " << argv[2];
            throw std::invalid_argument( err_msg_stream.str() );
         }
      } else if ( argc > 1 ) {
         debug_printf( debug, "argv[1] = %s\n", argv[1] ); 
         char* end_ptr = nullptr;
         num_vals = (int)strtoul( argv[1], &end_ptr, 10 );
         if  ( end_ptr == nullptr ) {
            err_msg_stream << "Invalid input: " << argv[1];
            throw std::invalid_argument( err_msg_stream.str() );
         }
      }
      
      std::string foo_str = "foo";
      double foo_double = 3.141592653589793238462f;
      debug_cout( debug, "Testing debug_cout: num_vals is ", 
            num_vals,", foo_str is ", foo_str, ", foo_double is ", 
            foo_double );

      test_my_file_io_funcs( filename, num_vals, inject_error, debug );
      
      return EXIT_SUCCESS;
   
   } catch( std::exception& ex ) {
      printf( "ERROR: %s\n", ex.what() ); 
      return EXIT_FAILURE;
   }
}

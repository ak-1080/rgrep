/**
 * The contents of this file are only a suggestion.
 * Feel free to change anything.
 */

#include "matcher.h"
#include <string.h>

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
 
 
 
  /*Akram 2014*/
  /*******************NOTE: with ? it messes up with \n inputs*/
 
 

int matches_leading(char *partial_line, char *pattern) {
  // You can use this recommended helper function, or not.
    char * line = partial_line;
    char * pat = pattern;
    char null = '\0';
   
    if(*(pat+1) == '?' && *(pat+2)==null)
        return 1;
    if(*pat == null)
        return 0;
    if(*line == null)
        return 0;
    
    int equal = 1;
    
    int backslash_dot = 0;
    int backslash_plus = 0;
    int backslash_q = 0;
    while(*pat != null && equal ){

                      
            int len = 0;
            int index = 0;
            char * p;
            
           
            int count =0;
              
            for(p = pattern; *p != null; p++)
                len++;
               
             for(p = pattern; *p != null && !index; p++){
                if( (*p) == '?')
                    index = count;
                    count++;
                }
               
            if(index && *(p-2) == '\\')
                backslash_q = 1;
           //checks '?'
           if(index && !backslash_q){
             
                 if(index == 1){ //a?xxx  will scan xxx in line
                    
                    //*pat = null;
                    //printf("Ptr %c\n",*(p));
                    if(*p == null)
                        return 1;
                    else
                        return matches_leading(line, p);
                
                }//beginning
                    
                if(index == len-1){//axx?
                   
                      *p = *(p-2)= null;
                       //printf("P %c\n",*(p-1));
                       puts(pat);
                     return matches_leading(line, pat);    
                
                 }
                
                 else{//any where in the middle aa?xx 
                
                
                   char new_pattern[70];
                   
                    strncpy(new_pattern, pattern, len);
                    new_pattern[len] = null; 
                   
                   p--;
                   
                   char *p2 = p-1;
                   //printf("? is at is %c\n", *(p2));
                   while(*(p+1) != null){
                    
                        char temp = *p;
                        *p = *(p+1);
                        *(p+1) = temp; 
                        
                        p++;
              
                   }
                    *p = null;// aa? too aa 
                    //*p = '\n'
                    
                    
                     //puts(pattern);
                    int eq_1 = matches_leading(partial_line, pattern);
                    
                    char temp = *(p2);
                    *(p2) = *(p2-1);
                    *(p2-1) = temp;
                    
                    //printf(" is at is %c\n", *(p2-1));
                    int eq_2 = matches_leading(partial_line, p2);
                    
                    //pattern = new_pattern;
                    
                    strncpy(pattern, new_pattern, len);
                    pattern[len] = null;
                    
                    puts(pattern);
                    
                    //puts(pat);
                    if(eq_1 || eq_2)
                        return  1;
                     else
                        return 0;
                  
                } 
           }
            
          
          if(*pat == '.' && !backslash_dot){
                  equal = 1;   
           
          }//if theres a dot and backslash not enabled
          
          
          else if(*pat == '+' && !backslash_plus){
        
            if(*(pat+1)== null)   
                return 1;
            *pat = null;
         
            equal = matches_leading(partial_line, pattern);
            
            printf("EQ is %d\n", equal);
            if( equal)
                return matches_leading(partial_line, pat+1);
            else 
                return 0;
        
        }
        
       
        
         else if(*pat == '\\'){
        
            if(*(pat+1)=='.')
                backslash_dot =1;
            if(*(pat+1)=='+')
                backslash_plus =1;
            if(*(pat+1)=='?')
                backslash_q =1;
                
             line--;
        }
        
        else if(*pat != *line){
             equal = 0;
            
           
            
             backslash_dot =0;
             backslash_plus =0;
             backslash_q =0;
            
        }
        
        
        if(*pat!= null && *line == null)      
                    return 0;
                  
            
       
       pat++;
       line++;    
    }
    
    
      
   
   
    if(!equal)
        return matches_leading(partial_line+1, pattern);
    else 
            return equal;
   
    
       

}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {

    
    return matches_leading(line, pattern);
    
}

#include <string.h>
#include <stdio.h>
#include  <ctype.h>


#define NUM_PRONOUNS 20
#define SIZE 20

//Forward references
void checker(char *story, char **pronouns, char **special, char **nouns);
int same_letters (char *x, char *y);
char *editWord(char **dest, char *symbol);
void printer(char **array);
char *editNoun(char **dest, char *symbol, char *buffer, int buffsize);
char *editPro(char **dest, char *symbol, char *buffer, int buffsize);




int main () {
   char story1[1200] = "A dog and her pups lived on a farm, where there was a well. The mother of the dog told the pups, do not go near the well or play around it. One of the pups wondered why they shouldn’t go to the well and decided to explore it. He went to the well. Climbed up the wall and peeked inside. In there, he saw his reflection and thought it was another dog. The pup saw that the other dog in the well (his reflection) was doing whatever he was doing, and got angry for imitating him. He decided to fight with the dog and jumped into the well, only to find no dog there. He barked and barked and swam until the farmer came and rescued him. Was this a lesson ? It sure was one.";
   char story2[1200] = "One day, a crab and his mother were on the beach, spending some time together. The crab gets up to move, but it can only walk sideways. His mother scolds him for walking sideways and asks him to walk forward by pointing his toes out front. The crab responds, \"I would like to walk forward, but I do not know how to\". Hearing this, his mom gets up to show him how, but even she is unable to bend her knees forward. She realizes that she was being unfair, apologizes sheepishly, and sits back in the sand.";
   char story3[1200] ="One day, a man was walking by a road when he heard a cat meowing from the bushes nearby. The cat was stuck and needed some help getting out. When the man reached out, the cat got scared and scratched the man. The man screamed loudly but didn’t back down. He tried again and again, even as the cat continued to scratch his hands. Another passerby saw this and said, \"Just let it be! The cat will find a way to come out later\". The man did not listen but tried until he helped the cat. Once he let the cat free, he told him \"The cat is an animal, and its instincts make him scratch and attack. I am a human and my instincts make me compassionate and kind. I also felt that this cat is cute\"."; 
  
   char *pronouns[NUM_PRONOUNS] = { "he","I","me","she","they","you","him","it",};
   char *nouns[NUM_PRONOUNS] = { "a","the","his","their","its","no","my","your",};
   char *special[NUM_PRONOUNS] ={"another","other","some","this","her",};
   

   checker(story1,pronouns,special,nouns);
   checker(story2,pronouns,special,nouns);
   checker(story3,pronouns,special,nouns);
   
}

/*
   Function: This function checks for pronouns, nouns and special words that are either nouns or pronouns
   in: takes in the story, ponouns, special and nouns arrays
   out: N/A

*/



void checker(char *story, char **pronouns, char **special, char **nouns){
   const char s[2] = " ";
   
   char *words[1200]={};
   char *word;
   int pronounCounter = 0;
   int nounCounter = 0;
   int result = 0;
   int result2 = 0;
   char comma[] = ",";
   char period[] = ".";
   char nounSym[] = ">";
   char proSym[] ="]";
   char *newStory[1200] ={};
   char buffer[SIZE];
   int checker1 = 0;
   int checker2;

   int proOne =0;
   int nounOne =0;
   
  

       //Storing words in a new array
        word = strtok(story, s);
        int i = 0;
        
        while( word != NULL ) {
            words[i] = word;    
            i++;
            word = strtok(NULL, s);
        }
                  
        for (int x =0; words[x] != NULL;x++){
            //Adding modified elements to the new array
            newStory[x] = words[x];
        
            for (int j = 0; pronouns[j] != NULL;j++){     
               //Checking for pronouns
               result = same_letters(pronouns[j],words[x]);
               if(result == 1 || strcasecmp(pronouns[j],words[x])==0){
                    newStory[x] = strdup(editPro(&words[x],proSym,buffer,SIZE));
                    pronounCounter++;
                    result = 0;
                }
                
      
            }
            //Noun finding
            for (int nouner = 0; nouns[nouner] != NULL; nouner++){
                 result2 = same_letters(nouns[nouner],words[x]);
                 if (result2 == 1 || strcasecmp(nouns[nouner],words[x])==0){
                   //Looping noun vs special cases elements
                   for (int findspec=0; special[findspec] != NULL; findspec++){     
                     if(strcasecmp(words[x], special[findspec])==0){
            
                       nounCounter--;
                     } 
                   }  
                 
                   newStory[x] = strdup(editNoun(&words[x],nounSym,buffer,SIZE));
                   nounCounter++;
                   result2 =0;
             
              }
              
            }

    
            //Special cases
            for (int spec =0; special[spec] != NULL; spec++){
             
              if (strcasecmp(special[spec],words[x])==0 && ((strcasecmp(words[x+1],"a")==0) || (strcasecmp(words[x+1],"and")==0))){
                newStory[x] = strdup(editPro(&words[x],proSym,buffer,SIZE));
                pronounCounter++;
                checker2 = 1;

              }
              //puncuation checking
              if (strcasecmp(editWord(&special[spec], comma),words[x]) == 0 || (strcasecmp(editWord(&special[spec], period),words[x]) == 0)){
                 newStory[x] = strdup(editPro(&words[x],proSym,buffer,SIZE));
                 pronounCounter++;
             
                 checker2 =1;
              }
             if(strcasecmp(special[spec],words[x])==0){
                newStory[x] = strdup(editNoun(&words[x],nounSym,buffer,SIZE));
                nounCounter++;   
              }             
            }
             //Checking if one is a noun or a pronoun 
            if(strcasecmp(words[x],"one")==0 && (strcasecmp(words[x+1],"of")==0) ){
                  newStory[x] = strdup(editPro(&words[x],proSym,buffer,SIZE));
                  pronounCounter++; 
                  proOne =1;
                                      
            }
            if(strcasecmp(words[x],"one.")==0 || (strcasecmp(words[x],"one,")==0) ){
                   newStory[x] = strdup(editNoun(&words[x],nounSym,buffer,SIZE));
                  nounCounter++;
              
                                         
            }
           if(strcasecmp(words[x], "one")==0 && proOne ==0) {
               newStory[x] = strdup(editNoun(&words[x],nounSym,buffer,SIZE));
              nounCounter++;
            }
         
          

        }
        printf("\n");
    
        printer(words);
        printf("\n\n");
        printf("This story had %d nouns and %d pronouns as follows: \n\n", nounCounter,pronounCounter);
        //print modified array
        printer(newStory);
        
}

/*
   Function: This functions checks if two strings are the same ignoring punctuation
   in: takes in the two strings
   out: int -> wheter two are same or not

*/
int same_letters (char *string1, char *string2) {
  //Checks if the char is an aphabet or not
  while (isalpha(*string1) || isalpha(*string2)) {
    if (*string1++ != *string2++) return 0;
  }
  return 1;
}

/*
   Function: this function was created for the special cases
             // Adds a comma or period to see if the word is and then it is compared to see if it a pronoun
   in: takes in the story array and puncutation (comma or period)
   out: returns the array

*/
char *editWord(char **dest, char *symbol){
    char result[50] = "";
    char *temp;
        strcat(result,*dest);
        strcat(result,symbol);
        temp = result;
        return temp;
     
}

/*
   Function: This functions adds the correct sybols for the pronouns
   in: takes takes in array element, the symbol (] for pronouns) and a buffer as a temp variable
   out: char variable

*/

char *editPro(char **dest, char *symbol, char *buffer, int buffsize) {
    if (buffsize < 1 + strlen(*dest) + strlen(symbol) + 1) {
        // need space for "[" + dest + comma + terminating '\0'
        buffer = "";
        return buffer;
    }
    strcpy(buffer, "[");
    strcat(buffer, *dest);
    strcat(buffer, symbol);
    return buffer;
}
/*
   Function: This functions adds the correct sybols for the nouns
   in: takes takes in array element, the symbol (> for nouns) and a buffer as a temp variable
   out: char variable

*/
char *editNoun(char **dest, char *symbol, char *buffer, int buffsize) {
    if (buffsize < 1 + strlen(*dest) + strlen(symbol) + 1) {
        // need space for "<" + dest + comma + terminating '\0'
        buffer = "";
        return buffer;
    }
    strcpy(buffer, "<");
    strcat(buffer, *dest);
    strcat(buffer, symbol);
    return buffer;
}
/*
   Function: This function prints the story using a for loop
   in: takes in the array needed to print
   out: N/A

*/
void printer(char **array){
   for (int i=0; array[i] != NULL; i++){
     printf("%s ", array[i]);
   }

}



/**
* Project: Implementace překladače jazyka IFJ21
*
* @brief Code generator 
*
* @author Martin Pech <xpechm00@stud.fit.vutbr.cz>
*/
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "codegen.h"


/** ===================================================================
* Generování záhlaví a funkce main
*/ 

// Generování hlavičky
void generateHeader(){
    printf("#Program started!");
    printf("\n.IFJcode21\n");
    printf("\nJUMP $$main");
}

// Generování Main scope
void generateMain(){
    printf("\n\n#Main function");
    printf("\nLABEL $$main");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR GF@_$StackTopValue");
    printf("\nDEFVAR GF@_$ml");
    printf("\nDEFVAR GF@_$st");
    printf("\nDEFVAR GF@_$res");
    printf("\nDEFVAR GF@_$trashStack");
}

// Generování konce Main scope
void generateMainEnd(){
    printf("\n\n#End of Main function");
    printf("\nPOPFRAME");
    printf("\nCLEARS");
    printf("\nEXIT int@0");
}


/** ===================================================================
* Volání vestavěných funkcí 
*/ 

// Built-in funkce substring
void BuiltIn_Substr (){
    printf("\n\n#Built-in function Substr");
    printf("\nLABEL $$substr");   
    printf("\nCREATEFRAME");              
    printf("\nPUSHFRAME");                       
    printf("\nDEFVAR LF@_$retval");              
    printf("\nDEFVAR LF@_$beginPos");
    printf("\nDEFVAR LF@_$endPos");
    printf("\nDEFVAR LF@_$givenString");
    printf("\nDEFVAR Lf@_$strLen");
    printf("\nPOPS LF@_$endPos");        
    printf("\nPOPS LF@_$beginPos");
    printf("\nPOPS LF@_$givenString");
    printf("\nSTRLEN LF@_$strLen LF@_$givenString #sizeof(string)");
    printf("\n# Testing positions:");
    printf("\nDEFVAR LF@_$testBounds");
    printf("\nGT LF@_$testBounds LF@_$endPos LF@_$strLen");
    printf("\nJUMPIFEQ $$substr_error LF@_$testBounds bool@true");
    printf("\nLT LF@_$testBounds LF@_$endPos int@1");
    printf("\nJUMPIFEQ $$substr_error LF@_$testBounds bool@true");
    printf("\n#");
    printf("\nGT LF@_$testBounds LF@_$beginPos LF@_$strLen");
    printf("\nJUMPIFEQ $$substr_error LF@_$testBounds bool@true");
    printf("\nLT LF@_$testBounds LF@_$beginPos int@1");
    printf("\nJUMPIFEQ $$substr_error LF@_$testBounds bool@true");
    printf("\n#");
    printf("\nGT LF@_$testBounds LF@_$beginPos LF@_$strLen");
    printf("\nJUMPIFEQ $$substr_error LF@_$testBounds bool@true");
    printf("\n#Substr implementation:");
    printf("\nSUB LF@_$beginPos LF@_$beginPos int@1");
    printf("\nGETCHAR LF@_$retval LF@_$givenString LF@_$beginPos");
    printf("\nADD LF@_$beginPos LF@_$beginPos int@1");
    printf("\nDEFVAR LF@_$tmpString");
    printf("\n#Substr Loop:");
    printf("\nLABEL $$substr_beginLoop");
    printf("\nJUMPIFEQ $$substr_endLoop LF@_$beginPos LF@_$endPos");
    printf("\nGETCHAR LF@_$tmpString LF@_$givenString LF@_$beginPos");
    printf("\nCONCAT LF@_$retval LF@_$retval LF@_$tmpString");
    printf("\nADD LF@_$beginPos LF@_$beginPos int@1");
    printf("\nJUMP $$substr_beginLoop");
    printf("\n# Substr EndLoop:");
    printf("\nLABEL $$substr_endLoop");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
    printf("\n# Substr Error");
    printf("\nLABEL $$substr_error");
    printf("\nMOVE LF@_$retval string@");   
    printf("\nPUSHS LF@_$retval");             
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Built-in funkce reads
void BuiltIn_Reads(){
    printf("\n\n#Built-in function Reads");
    printf("\nLABEL $$reads");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nREAD LF@_$retval string");        //TODO ověření španého vstupního řetězce
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Built-in funkce readi
void BuiltIn_Readi(){
    printf("\n\n#Built-in function Readi");
    printf("\nLABEL $$readi");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nDEFVAR LF@_$checkval");
    printf("\nREAD LF@_$retval int");
    printf("\nTYPE LF@_$checkval LF@_$retval");
    printf("\nJUMPIFEQ $$isInt LF@_$checkval string@int");
    printf("\nMOVE LF@_$retval nil@nil");
    printf("\nLABEL $$isInt");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Built-in funkce readn
void BuiltIn_Readn(){
    printf("\n\n#Built-in function Readn");
    printf("\nLABEL $$readn");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nDEFVAR LF@_$checkval");
    printf("\nREAD LF@_$retval float");
    printf("\nTYPE LF@_$checkval LF@_$retval");
    printf("\nJUMPIFEQ $$isFloat LF@_$checkval string@float");
    printf("\nMOVE LF@_$retval nil@nil");  
    printf("\nLABEL $$isFloat");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Built-in funkce Chr
void BuiltIn_Chr(){
    printf("\n\n#Built-in function Chr");
    printf("\nLABEL $$chr");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nDEFVAR LF@_$ascii");
    printf("\nPOPS LF@_$ascii");

    //ověření zda je cislo? o.O

    printf("\nDEFVAR LF@_$checkval");
    printf("\nGT LF@_$checkval LF@_$ascii int@255");
    printf("\nJUMPIFEQ $$chr_error LF@_$checkval bool@true");
    printf("\nLT LF@_$checkval LF@_$ascii int@0");
    printf("\nJUMPIFEQ $$chr_error LF@_$checkval bool@true");
    //
    printf("\nINT2CHAR LF@_$retval LF@_$ascii");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
    
    //error
    printf("\nLABEL $$chr_error");
    printf("\nMOVE LF@_$retval nil@nil");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

//Built-in funkce Ord
void BuiltIn_Ord(){
    printf("\n\n#Built-in function ord");
    printf("\nLABEL $$ord");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nDEFVAR LF@_$givenPos");
    printf("\nDEFVAR LF@_$givenStr");
    printf("\nPOPS LF@_$givenPos");
    printf("\nPOPS LF@_$givenStr");
    printf("\n# Ord position & string check");
    printf("\nDEFVAR LF@_$testBounds");
    printf("\nDEFVAR LF@_$strLen");
    printf("\nSTRLEN LF@_$strLen LF@_$givenStr");
    printf("\nGT LF@_$testBounds LF@_$givenPos LF@_$strLen");
    printf("\nJUMPIFEQ $$ord_error LF@_$testBounds bool@true");
    printf("\nLT LF@_$testBounds LF@_$givenPos int@1");
    printf("\nJUMPIFEQ $$ord_error LF@_$testBounds bool@true");
    printf("\n# Ord function implementation");
    printf("\nSTRI2INT LF@_$retval LF@_$givenStr LF@_$givenPos");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
    printf("\n# Ord error");
    printf("\nLABEL $$ord_error");
    printf("\nMOVE LF@_$retval nil@nil");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

void BuiltIn_Float2Int(){
    printf("\n\n#Built-in function float2int");
    printf("\nLABEL $$float2int");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    printf("\nPOPS LF@_$retval");
    printf("\nJUMPIFEQ $$float2int_returnNil LF@_$retval nil@nil");
    printf("\nDEFVAR LF@_$typeOfNum");
    printf("\nTYPE LF@_$typeOfNum LF@_$return");
    printf("\nJUMPIFEQ $$float2int_end LF@_$typeOfNum string@string");
    printf("\nJUMPIFEQ $$float2int_end LF@_$typeOfNum string@float");

    printf("\nFLOAT2INT LF@_$retval LF@_$retval");
    printf("\nJUMP $$float2int_end");

    printf("\nLABEL $$float2int_returnNil");
    printf("\nMOVE LF@_$retval nil@nil");

    printf("\nLABEL $$float2int_end");
    printf("\nPUSHS LF@_$retval");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Počátek funkce
void BuiltIn_WriteBegin(){                                              
    printf("\nLABEL $$writeBI");            //!POZOR NA JMÉNO FUNKCE
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$toWrite");
    printf("\nDEFVAR LF@_$checkNil");
}

// Volání jednotlivých prvků funkce (Honza říkal že bude posílat po jednom)
void BuiltIn_WriteInsert(){
    printf("\nPOPS LF@_$toWrite");
    printf("\nTYPE LF@_$checkNil LF@_$toWrite");
    printf("\nJUMPIFEQ $$foundNil");
    printf("\nWRITE LF@_$toWrite");
}

// Konec funkce
void BuiltIn_WriteEnd(){
    printf("\nPOPFRAME");
    printf("\nRETURN");

    printf("\nLABEL $$foundNil");       //if stack->top == nil@nil >> print string@nil
    printf("\nWRITE string@nil");
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Nepožadovaná funkce clearStack, uvolní zásobník
void BuiltIn_clearStack(){
    printf("\n#Built-in clearStack");
    printf("\nLABEL $$clearStack");
    printf("\nMOVE GF@_$clearStackVar bool@true");
    printf("\nJUMPIFEQ $$clearStack_end GF@_$StackTopValue bool@true");
    printf("\nPOPS GF@_$trashStack");
    printf("\nJUMP $$clearStack");
    printf("\nLABEL $$clearStack_end");
    printf("\nRETURN");
}

// Nepožadovaná funkce decision -> použití pro vyhodnocení výrazu podmínky
void BuiltIn_decision(){
    printf("\n\n#BuiltIn decision");
    printf("\nLABEL $$decision");
    printf("\nPOPS GF@_$StackTopValue");
    printf("\nJUMPIFEQ $$isEqual GF@_$StackTopValue bool@true");
    printf("\nPUSHS nil@nil");
    printf("\nRETURN");

    printf("\nLABEL $$isEqual");
    printf("\nPUSHS int@1");
    printf("\nRETURN");
}

// Nepožadovaná funkce notDecision -> použití pro vyhodnocení výrazu podmínky
void BuiltIn_notDecision(){
    printf("\n\n#BuiltIn not decision");
    printf("\nLABEL $$notDecision");
    printf("\nPOPS GF@_$StackTopValue");
    printf("\nJUMPIFNEQ $$isNotEqual GF@_$StackTopValue bool@false");
    printf("\nPUSHS nil@nil");
    printf("\nRETURN");

    printf("\nLABEL $$isNotEqual");
    printf("\nPUSHS int@1");
    printf("\nRETURN");
}

/*void BuiltIn_toInteger(){
    printf("\n\nBuiltIn toInteger");
    printf("\nLABEL $$toInteger");
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");

}*/
//funkce toInteger - už existuje float2int
//kontrola builtIn funkcí.

// Funkce generující vestavěné funkce
void generateBuiltIn(){
    BuiltIn_Chr();
    BuiltIn_Ord();
    BuiltIn_Readi();
    BuiltIn_Readn();
    BuiltIn_Reads();
    BuiltIn_Substr();
    //BuiltIn_toInteger();
    BuiltIn_Float2Int();
    BuiltIn_decision();
    BuiltIn_notDecision();
    BuiltIn_clearStack();
    //BuiltIn_Write(); -> ten tu nebude, ten musíš obhospodařit sám, pokud chceš posílat jeden argument za druhým
}

/** ===================================================================
* Funkce pro vložení prvku na zásobník
*/  

// Funkce přidá variable libovolného typu na stack
void addVarOnTop(char *variableName, char *type){
    printf("\nPUSHS %s@_%s", type, variableName);
}

// Funkce přidá const libovolného typu na stack
void addConstOnTop(char *value, char *type){
    printf("\nPUSHS %s@%s", type, value);
    //nelze využít pro typ float!!! -> užij funkci AddNumberOnTop();
}

// Pomocné funkce na PUSHS - pro použití kompletně stačí dvě funkce nahoru
// Pomocná funkce na přidání lokální proměnné 
void addLocalVarOnTop(char *variableName){
    printf("\nPUSHS LF@_%s", variableName);
}

// Pomocná funkce isInteger pro funkci AddNumOnTop
/*bool isInteger(float value){
    int isInt = (int)value;
    if (isInt != 0){
        return false;
    }
    return true;
}*/

// Funkce pro vložení prvku na zásobník -- probably useless -> vše přes string
/*void AddNumOnTop(float value){ 
        printf("\n\n#Function AddNumOnTop");
        isInteger(value);
        if(isInteger){
            int convInt = (int)value;
            printf("\nPUSHS int@%d", convInt);
        }
        else{
            printf("\nPUSHS float@%a", value); //format 0x0p+0.. wtf?
        }
}*/

void AddNumberOnTop(char *value){
    printf("\nPUSHS float@%a", value);
}

void AddIntOnTop(char *value){
    printf("\nPUSHS int@%d", value);
}

// Funkce pro vložení strinu na zásobník
void AddStringOnTop(char *value){
    printf("\n\n#Function AddStringOnTop");
    printf("\nPUSHS string@%s", value);
}

// Funkce přidá nil na vrchol stacku
void AddNilOnTop(){
    printf("\nPUSHS nil@nil");
}

// Pomocná funkce vracející návratovou proměnnou na stack
void functionRetval(){
    printf("\nPUSHS LF@_$retval");
}

/** ===================================================================
* Funkce pro čtení prvku ze zásobníku
*/

// Čtení prvku ze zásobníku
void ReadTop(){
    printf("\n\n#Function ReadTop");
    printf("\nPOPS GF@_$StackTopValue");
}

// Čtení prvku ze zásobníku a uložení do libovolné proměnné (např u funkcí)
void ReadTopTo(char *variableName){
    printf("\nPOPS LF@_%s", variableName);
}
 
// Okamžitý výpis POPnuté hodnoty
void PrintReadTopResult(){
    printf("\nWRITE GF@_$StackTopValue");
}

/** ===================================================================
* Funkce pro operace s prvky a s prvky zásobníku
*/

// Sečtení dvou čísel na zásobníku - uložení na top
void StackAdds(){ 
    printf("\n\n#Function ADDS");
    printf("\nADDS");
}

// Sečtení dvou čísel
void Add(char *type, char *retval, char* firstArg, char* secondArg){
    printf("\nADD %s@_%s %s@_%s %s@_%s", type, retval, type, firstArg, type, secondArg);
}

// Odečte dvě hodnoty na zásobníku
void StackSubs(){
    printf("\n\n#Function SUBS");
    printf("\nSUBS");
}

// Odečte dvě hodnoty
void Sub(char *type, char *retval, char* firstArg, char* secondArg){
    printf("\nSUB %s@_%s %s@_%s %s@_%s", type, retval, type, firstArg, type, secondArg);
}

// Vynnásobí dvě hodnoty na zásobníku
void StackMuls(){
    printf("\n\n#Function MULS");
    printf("\nMULS");
}

// Vynnásobí dvě hodnoty
void Mul(char *type, char *retval, char* firstArg, char* secondArg){
    printf("\nMUL %s@_%s %s@_%s %s@_%s", type, retval, type, firstArg, type, secondArg);
}

// Podělí dvě hodnoty float & float na zásobníku
void StackDivs(){
    printf("\n\n#Function DIVS");
    printf("\nDIVS");
}

// Podělí dvě hodnoty float & float
void Div(char *type, char *retval, char* firstArg, char* secondArg){
    printf("\n\nDIV %s@_%s %s@_%s %s@_%s", type, retval, type, firstArg, type, secondArg);
}

// Podělí dvě hodnoty int & int na zásobníku
void StackIdivs(){
    printf("\n\n#Function IDIVS");
    printf("\nIDIVS");
}

// Podělí dvě hodnoty int & int
void Idiv(char *type, char *retval, char* firstArg, char* secondArg){
    printf("\nIDIV %s@_%s %s@_%s %s@_%s", type, retval, type, firstArg, type, secondArg);
}

// Funkce převede celočíselný int na float
void int2floats(){
    printf("\nINT2FLOATS");
}
void int2floats2(){
    ReadTop();
    int2floats();
    printf("PUSHS GF@_$StackTopValue");
}

/** ===================================================================
* Funkce porovná dva prvky v případě neúspěchu vrátí na stack nil@nil
*/

// TOP == TOP - 1
void stackTopEqualToNext(){
    printf("\nEQS");
    printf("\nCALL $$decision");
}

// TOP != TOP - 1
void stackTopNotEqualToNext(){
    printf("\nEQS");
    printf("\nCALL $$notDecision");
}

// TOP < TOP - 1
void bigger(){
    printf("\nPOPS GF@_$ml");
    printf("\nPOPS GF@_$st");
    printf("\nGT GF@_$res GF@_st GF@_ml");
    printf("\nPUSHS GF@_$res");
    printf("\nCALL $$decision");
}

// TOP <= TOP - 1
void biggerEqual(){
    printf("\nPOPS GF@_$ml");
    printf("\nPOPS GF@_$st");
    printf("\nGT GF@_$res GF@_$ml GF@_st");
    printf("\nPUSHS GF@_$res");
    printf("\nCALL $$notDecision");
}

// TOP > TOP - 1
void smaller(){
    printf("\nPOPS GF@_$ml");
    printf("\nPOPS GF@_$st");
    printf("\nLT GF@_$res GF@_st GF@_ml");
    printf("\nPUSHS GF@_$res");
    printf("\nCALL $$decision");
}

// TOP >= TOP - 1
void smallerEqual(){
    printf("\nPOPS GF@_$ml");
    printf("\nPOPS GF@_$st");
    printf("\nLT GF@_$res GF@_$ml GF@_st");
    printf("\nPUSHS GF@_$res");
    printf("\nCALL $$notDecision");
}

/** ===================================================================
* Funkce pro obecné ovládání pseudoAssembleru
*/

void createFrame(){
    printf("\nCREATEFRAME");
}

void pushFrame(){
    printf("\nPUSHFRAME");
}

void popFrame(){
    printf("\nPOPFRAME");
}

void trashStack(){
    printf("\nPOPS GF@_$trashStack");
}

void makeLabel(char *labelName){
    printf("\nLABEL $%s", labelName);
}

void createLocalVar(char *varName){
    printf("\nDEFVAR LF@%s", varName);
}

void strlenFunction(){
    ReadTop();
    printf("\nSTRLEN GF@_$StackTopValue GF@_$StackTopValue");
    printf("\nPUSHS GF@_$StackTopValue");
}

//volání funkce
void functionCall(char *functionName){  
    printf("\n\n#Function call");
    printf("\nCALL $%s", functionName);
}

//volání programových funkcí
void programFunctionCall(char *functionName){
    printf("\n\n#Program function call");
    printf("\nCALL $$%s", functionName);
}

// Funkce, která na dno zásobníku uloží hodnotu bool@true -> používá se k vyprázdněn stacku
void stackInitBool(){
    printf("\nDEFVAR GF@_$clearStackVar");
    printf("\nPUSHS bool@true");
}

// Funkce zavolá built-in funkci a vyčíštění zásobníku
void clearStack(){
    programFunctionCall("clearStack");
}

void concatVars(){
    trashStack();
    ReadTop();
    printf("\nCONCAT GF@_$StackTopValue GF@_$trashStack GF@_$StackTopValue");
    printf("\nPUSHS GF@_$StackTopValue");
}


/** ===================================================================
* Funkce pro generování funkce
*/

// Start funkce
void functionStart(/*int arrSize,*/ char *functionName/*, char *ArrayOfParams[]*/){  //Uložil jméno tohoto na stack?
    printf("\nJUMP $%s_end", functionName);
    printf("\n\n#Function %s_start", functionName); //_start??
    printf("\nLABEL $%s", functionName);
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    /*for(int i = 0; i+1 <= arrSize; i++){
        printf("\nDEFVAR LF@_%s", ArrayOfParams[i]);
        printf("\nPOPS LF@_%s", ArrayOfParams[i]);      //více returnů
    }*/
}

/* Funkce, která přijmá parametry pevně dané, nikoliv ze zásobníku 
void staticFunctionStart(int arrSize, char *functionName, char *ArrayOfParams[]){  //Uložil jméno tohoto na stack?
    printf("\nJUMP $%s_end", functionName);
    printf("\n#Function %s_start", functionName);
    printf("\nLABEL $%s", functionName);
    printf("\nCREATEFRAME");
    printf("\nPUSHFRAME");
    printf("\nDEFVAR LF@_$retval");
    for(int i = 0; i+3 <= arrSize; i = i+3){
        printf("\nDEFVAR LF@_%s", ArrayOfParams[i]);
        
        if(ArrayOfParams[i+1] == "string")
            printf("\nMOVE LF@_%s string@%s", ArrayOfParams[i], ArrayOfParams[i+2]);
        else if(ArrayOfParams[i+1] == "int")
            printf("\nMOVE LF@_%s int@%s", ArrayOfParams[i], ArrayOfParams[i+2]);
        else if(ArrayOfParams[i+1] == "bool")
            printf("\nMOVE LF@_%s bool@%s", ArrayOfParams[i], ArrayOfParams[i+2]);
        else if(ArrayOfParams[i+1] == "float")
            printf("\nMOVE LF@_%s float@%s", ArrayOfParams[i], ArrayOfParams[i+2]);
        else
            printf("\nMOVE LF@_%s nil@nil");
    }
}
*/

// Vytvoří return z funkce
void functionEnd(){   // Když dostanu počet zanoření můžu udělat cyklus na popnutí framů
    printf("\nPOPFRAME");
    printf("\nRETURN");
}

// Zavolá návěští za funkcí 
void functionEndLabel(char *functionName){
    printf("\nLABEL $%s_end", functionName);
}

/** ===================================================================
* Funkce pro generování cyklu
*/

// Generuje label funkce    
void generateWhileLabel(int nthWhile){
    printf("\n\n#Function While Label");
    printf("\nLABEL $while%d_start", nthWhile);
}

// Generuje počátek While smyčky
void generateWhile(int nthWhile, int toNumber){
    //vyhodnocení výrazu

    ReadTop();
    printf("\nJUMPIFEQ $while%d_end GF@_$StackTopValue nil@nil", nthWhile);
    printf("\nCREATEFRAME");

    for(int i = 0; i < toNumber; i++){
        printf("\nDEFVAR TF@_$%d", i);
        printf("\nMOVE TF@_$%d LF@_$%d", i, i);
    }
    printf("\nPUSHFRAME");
    
    //Doplnění těla while

}

// Generuje konec While smyčky
void generateWhileEnd(int nthWhile, int toNumber){
    printf("\nPOPFRAME");

    for(int i = 0; i < toNumber; i++){              //Možná chyba toNumber je o +- 1 (počet čísel)
        printf("\nMOVE LF@_$%d TF@_$%d", i, i);
    }
    printf("\nJUMP $while%d_start", nthWhile);
    printf("\nLABEL $while%d_end", nthWhile);
}

/** ===================================================================
* Funkce pro generování podmínky
*/

// Generuje počátek podmínky
void generateIf(int nthIf, int toNumber){
    ReadTop();
    printf("\nJUMPIFEQ $if%d_else GF@_$stackTopValue nil@nil", nthIf);

    printf("\nCREATEFRAME");

    for(int i = 0; i < toNumber; i++){
        printf("\nDEFVAR TF@_$%d", i);
        printf("\nMOVE TF@_$%d LF@_$%d", i, i);
    }
    printf("\nPUSHFRAME");

    //Doplnění těla if
}

// Generuje Else (else if) větev
void generateElse(int nthIf, int toNumber){
    printf("\nJUMP $if%d_end");
    printf("\nLABEL $if%d_else");
    printf("\nCREATEFRAME");

    for(int i = 0; i < toNumber; i++){
        printf("\nDEFVAR TF@_$%d", i);
        printf("\nMOVE TF@_$%d LF@_$%d", i, i);
    }
    printf("\nPUSHFRAME");
}

// Ukončení prováděné podmínky
void generateIfEnd(int nthIf, int toNumber){
    printf("\nLABEL $if%d_end");
    printf("\nPOPFRAME");
    for(int i = 0; i < toNumber; i++){              //Možná chyba toNumber je o +- 1 (počet čísel)
        printf("\nMOVE LF@_$%d TF@_$%d", i, i);
    }
}

/** ===================================================================
* Some Unused Sh*t :)
*/


// Funkce na přesun rámce výš

/*void generateIf(char *operation){
    printf("CREATEFRAME");
    printf("PUSHFRAME");
    printf("DEFVAR LF@_cond1");
    printf("POPS LF@_cond1");
    printf("DEFVAR LF@_cond2");
    printf("POPS LF@_cond2");

    printf("TYPE ")
}*/

/** ===================================================================
* Funkce pro generování funkce
*/

//Tělo?? - dostanu call na tuto funkci, vezmu name fce ze stacku a doplním? nakonci volám functionEnd();
//void codegenFlush(char *destinationFile){
//}

/* Ověření vygenerování kódu
bool codeGenerated(){
    if(generateHeader() == true && generateMain() == true && generateMainEnd() == true){
        return true;
    }
    return false;
}*/


//Dojde k vytvoření switche, který bude rozhodovat o prováděných operacích
//Pouze pro generování složitějších operací

/*
int generateInstruction(datatype *list){
    while(list->first != NULL){
        switch(list->first->instruction){
            case(IFbegin):
                generateIf(list, list->first->instruction);
                break;
            
        }
        list = list->right->right;
    }
}*/
/*
void generateIf(datatype *list, ){
    depth++;
    
    printf("\nCREATEFRAME");
    // Správa rámců?
    printf("\nPUSHFRAME");
    // Zjištění podmínky
    list->first = list->first->right;
    generateInstruction(list);
}*/




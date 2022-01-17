#include "syntaktick.h"
#include "codegen.h"

#include "typeZas.h"

//#define DEBUGER
#ifdef DEBUGER
char velmiMalePoleZnaku[90] = {'\0'};
#define inFc                fprintf(stderr, "%d > %.*s >> %s\n",err,(DEBUG_ODSAZ++)*2," | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |",__FUNCTION__)
#define midFc(TEXT_V_MAKRU) fprintf(stderr, "%d - %.*s -- %s\n",err,(DEBUG_ODSAZ)*2  ," | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |", TEXT_V_MAKRU)
#define outFc               fprintf(stderr, "%d < %.*s << %s\n",err,(--DEBUG_ODSAZ)*2," | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |", __FUNCTION__)
int DEBUG_ODSAZ = 0; 
#else//DEBUGER
#define inFc (0==0)
#define outFc (0==0)
#define midFc(TEXT_V_MAKRU) (0==0)
#endif//DEBUGER


typedef enum errKode{
    ok,
    ERR_UNKNOVN,//treba overit kam vsude patri, ve vysledku by nemel byt volan
    ERR_SEMANTIKA,
}errKode;
//help fc
token_t tokenGlobal;
bool tokenGlobalUsed = false;
errKode err = ok;


void intiToken(token_t* token){

    if(OK_CHAR_APP != appCharConstructor(&(token->attribute))){
        exit(-1);
    }
}

//Vola exit
void next(token_t* token, bool option){
    
    //inFc;
    if(tokenGlobalUsed){//Prepsat na static? TO DO
        intiToken(token);
        appCharToAppChar(&(token->attribute), (tokenGlobal.attribute));//hluboka
        token->type = tokenGlobal.type;//hluboka
        
        tokenGlobalUsed = false;
        //*token = tokenGlobal;//melka kopie
    }
    else{
        //destToken(&tokenGlobal);
        intiToken(token); //TO DO tato inicializace byla prozatimni, nyni ji nenecham? Treba predelat zbytek kodu.
        int ret = get_next_token(token,option);
        switch(ret){
            case 0:
                //outFc;
                break;
            case 1:
            case 2:
            default:
                //ERROR STATE TO DO
                // OSETRIT CHYBY ALLOCACE A TAK
                exit(1);    
        }
    }
    //midFc("\npalti A");
    appCharToAppChar(&(tokenGlobal.attribute), token->attribute);//hluboka
    tokenGlobal.type = token->type;//hluboka
    //midFc("\nA proto i B");
    return;
}

void back(token_t token){
    
    //tokenGlobal = token;
    tokenGlobalUsed = true;
}

///fc jednotlivych pravidel



// S-->require "ifj21" kodG
bool ruleS( htab_t** fc_table, tsStack_t** prom_table){
    
    inFc;
    token_t token;
    next(&token, true);
    if( token.type != REQUIRE_KW){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    midFc("ANO");
    destToken(&token);
    next(&token, true);
    if(token.type !=  STRING_IN_QUOTATION){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    midFc("ANO");
    if(0 != appCharCmpStr(token.attribute, "ifj21")){
        //printf("NE%s\n", token.attribute text);
        err = ERR_UNKNOVN;
        return false;
    }
    //printf("ANO\n");
    //Tady asi bude semanticka akce TO DO
    generateHeader();
    generateBuiltIn(); //pozor neni write
    
    if(!ruleKodG(fc_table, prom_table)){
        return false;
    }
    generateMainEnd();
    destToken(&token);
    outFc;
    return true;
    
}

bool ruleKodG( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    back(token);//Vracel bych ho vsude krom chyboveho stavu
    bool result = false;
    //(Odkladam precteni tokenu, pravdepodobne to jde i bez odkladani, ale to bych musel prepracovat pravidla)
    switch (token.type){
        case FUNCTION_KW:
            result = ruleDefFC(fc_table, prom_table);
            break;
        case GLOBAL_KW:
            result = ruleDecleFC(fc_table, prom_table);

            //Tady asi bude semanticka akce TO DO
            break;
        case ID: //case INTEGER: case NUMBER: case STRING_IN_QUOTATION: TO DO co to tu delalo ma to byt jinde?
        case READI_KW:
        case READN_KW:
        case READS_KW:
        case WRITE_KW:
        case SUBSTR_KW:
        case CHR_KW: //TO DO dopsat tuto fc
        case ORD_KW:
        case TOINTEGER_KW: // Zde je vic case za sebou na jeden zpusob reseni
            //Tady asi nebude semanticka akce TO DO
            result = ruleVolaniFc(fc_table, prom_table);

            clearStack();
            break;

            //Tady asi bude semanticka akce TO DO
            break;
        case END://Jediny pripad pro Epsilon pravidlo
            
            //Tady asi bude semanticka akce TO DO
            result = true;
            break;//Konec vstupu
        default: //Chybny vstup --> chyba
            err = ERR_UNKNOVN;
            result = false;
            break;
    }

    if(!result){
        destToken(&token);
        return false;
    }

    if(!ruleKodG(fc_table, prom_table)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    outFc;
    return true;

    
}
bool ruleDecleFC( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    midFc("ANB");
    //midFc("ANO");
    
    if(token.type == GLOBAL_KW){
        //Tady asi nebude semanticka akce TO DO

        bool ret = ruleDecleFC2(fc_table, prom_table );
        //midFc("KKK");
        outFc;
        destToken(&token);
        return ret;
    }
    err = ERR_UNKNOVN;
    //midFc("NE");
    outFc;
    destToken(&token);
    return false;
}



bool ruleDecleFC2( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    midFc("OO\n");
    next(&token, true);
    midFc("bb\n");
    if(token.type != ID){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    midFc("NE\n");
    if(!sem_FCIdDecler(token, fc_table, prom_table)){
        err = ERR_UNKNOVN;//Spatny nazev identifikatoru (vycenasobne definice)
        destToken(&token);
        return false;
    }

    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }


    midFc("ANOJJJJJJJJJJJJJJJJ\n");
    bool ret = ruleDecleFC3(fc_table, prom_table, name);
    outFc;
    
    destToken(&token);
    free(name);
    return ret;
    
}

bool ruleDecleFC3( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){

    inFc;
    //Tady bude treba rict semantice ze se zanoruji do fc
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;//
    }
    if(!ruleSeznamParam(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;//
    }
    #ifdef DEBUGER

    fprintf(stderr, "Parm number %d =======================================================\n", htab_get_data(*fc_table, nameFc)->input_type_len);
    fprintf(stderr,"table top pointer %p\n",ts_top(*prom_table) );
    #endif
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;//
    }
    destToken(&token);
    next(&token, true);
    //fprintf(stderr,"JAAAA HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
    midFc(token.attribute.text);
    if(token.type != VAR_INIT){
        //err = ERR_UNKNOVN;
        back(token);//FC nic nevraci
        destToken(&token);
        return true;//
    }
    //fprintf(stderr,"JAAAA HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
    
    if(!ruleSeznamRet(fc_table, prom_table, nameFc)){
        destToken(&token);
        ts_pop(*prom_table);
        return false;//
    }
    //Tady asi bude semanticka akce TO DO
    //Bude potrebovat inf, z seznam Param a ret
    destToken(&token);
    outFc;
    ts_pop(*prom_table);
    return true;
}

/**/
bool ruleDecleProm( htab_t** fc_table, tsStack_t** prom_table){
    inFc;

    token_t token;
    next(&token, true);
    //midFc("ANO");
    if(token.type != LOCAL_KW){
        //Tady asi nebude semanticka akce TO DO
        err = ERR_UNKNOVN;    
        outFc;
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != ID){

        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    
    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
    return false;
    }
    
    destToken(&token);
    //bool definovano = false;
    bool nula = false;
    bool nil = false;

    token_t token2;
    next(&token2, true);
    
    if(token2.type != VAR_INIT){
        err = ERR_SEMANTIKA;
        destToken(&token2);
        destToken(&token);
        return false;
    }
    destToken(&token2);
    next(&token2, true);
    if( !(token2.type == INTEGER_KW || token2.type == STRING_KW || token2.type == NUMBER_KW)){
        err = ERR_SEMANTIKA;
        destToken(&token2);
        destToken(&token);
        return false;
    }
    type_t vyzadovane;
    vyzadovane = redukce(token2.type);
    //back(token);
    //typZas_init(&vyzadovane);
    destToken(&token2);
    next(&token2, true);
    if(token2.type == ASSIGN){
        if(!rulePrirazovaneAB(fc_table, prom_table, vyzadovane, &nula, &nil)){
            destToken(&token2);
            //destToken(&token);

            return false;
        }
         //očekává param varName
    }
    else{
        nil = true;
        back(token2);
        AddNilOnTop();
         //očekává varName
    }
    destToken(&token2);
    


    bool chybaPameti = false;
    if(!sem_PromDef(name, fc_table, prom_table, vyzadovane, &chybaPameti, nula, nil)){
        if(chybaPameti){
            err = ERROR_ALLOCATION;    
            return false;
        }
        err = ERR_UNKNOVN;//Spatny nazev identifikatoru (vycenasobne definice)
        //destToken(&token);
        return false;
    }

    
    char* id = htab_get_data(ts_top(*prom_table)->tab, name)->id;
    free(name);
    name = NULL;    
    
    createLocalVar(id);
    
    
    ReadTopTo(id);
    outFc;
    
    return true;
}

bool rulePrirazovaneAB( htab_t** fc_table, tsStack_t** prom_table, type_t vyzadovane, bool* nula, bool* nil){
//TO DO kontroly
    inFc;
    token_t token;
    next(&token, true);
    back(token);
    type_t typ;
    if(sem_isFC(token, fc_table, prom_table)){
        
        if(!ruleVolaniFc(fc_table, prom_table)){
            destToken(&token);
            return false;
        }
        //semantika a volani fc
        destToken(&token);
        return true;
    }else{
        if(!ruleHodnotaR(fc_table, prom_table, &typ)){
            destToken(&token);
            return false;
        }
        if(vyzadovane != typ){
            if(vyzadovane == NUMBER_T && typ == INTEGER_T){
                int2floats();
            }else{
                destToken(&token);
                err = ERR_SEMANTIKA;
                return false;        
            }
        }
        //semanticka akce bude tady
        outFc;
        destToken(&token);
        return true;
    }
}


bool ruleDefFC( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    midFc("ANO");
    if(token.type != FUNCTION_KW){
        err = ERR_UNKNOVN;
        //midFc("NE");
        //outFc;
        destToken(&token);
        return false;
    }
    //Tady asi nebude semanticka akce TO DO
    bool ret = ruleDefFC2(fc_table, prom_table);
    midFc("KKKO");
    outFc;
    destToken(&token);
    return ret;

}

bool ruleDefFC2(htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    midFc("NE");
    if(token.type != ID){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    midFc("NE2");
    if(!sem_FCIdDef(token, fc_table, prom_table)){
        err = ERR_UNKNOVN;//Spatny nazev identifikatoru (vycenasobne definice)
        destToken(&token);
        return false;
    }
    midFc("NE3");

    

    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }
    

    functionStart(name);
    bool ret = ruleDefFC3(fc_table, prom_table, name);
    outFc;    
    
    if(!ruleSlozenyPrikaz(fc_table, prom_table, name)){
        destToken(&token);
        free(name);
        ts_pop(*prom_table);
        return false;//
    }
    ts_pop(*prom_table);
    generateReturn(htab_get_data(*fc_table, name)->output_type_len);//TO DO zajisti ze neco najde
    functionEnd();
    functionEndLabel(name);
    
    free(name);
    name = NULL;
    

    destToken(&token);
    outFc;
    return ret;
    
}
bool ruleDefFC3( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){

    inFc;
    //Tady bude treba rict semantice ze se zanoruji do fc
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;//
    }
    midFc("Krajta");
    if(!ruleSeznamParam(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;
    } 
    #ifdef DEBUGER
    fprintf(stderr, "Parm number Def %d =======================================================\n", htab_get_data(*fc_table, nameFc)->input_type_len);
    fprintf(stderr,"table top pointer %p\n",ts_top(*prom_table) );
    fprintf(stderr, "Par name %s is %p \n",velmiMalePoleZnaku ,ts_find_item(*prom_table, velmiMalePoleZnaku));
    fprintf(stderr, "Pocet v tabulce %d a pod ni %d \n",ts_top(*prom_table)->current_items,ts_top(*prom_table)->items_lower);
    //fprintf(stderr, "Lezu kam nemam %p \n",ts_top(*prom_table)->tab);
    
    #endif
    midFc("KARATE");
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;//
    }
    
    midFc(token.attribute.text);//Debugovy vypis porusuje zapouzdreni, ale co ten fungovat nemusi Na spatnem miste
    destToken(&token);
    next(&token, true);
    //fprintf(stderr,"JAAAA HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
    if(token.type != VAR_INIT){//TO DO opravit (napsat spravne)
        //err = ERR_UNKNOVN;
        back(token);//FC nic nevraci
        destToken(&token);
        outFc;
        return true;//
    }else{
    //fprintf(stderr,"JAAAA HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
    
        if(!ruleSeznamRet(fc_table, prom_table, nameFc)){
            destToken(&token);
            return false;//
        }
    }

    //Tady asi bude semanticka akce TO DO
    //Bude potrebovat inf, z seznam Param a ret
    
    destToken(&token);

    outFc;
    return true;
}
void generateReturn(int a){
    for(int i = 0; i < a; i++){
        AddNilOnTop();
    }
}


//Asi bude treba vracet neco extra
bool ruleSeznamParam( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    ts_push_fresh(*prom_table);
    token_t token;
    next(&token, true);
    
    //int zanoreni = 0;
    //if () //CHYBA nevim co tento if mel delat, nyni je odstranen
    
    bool defined = htab_find(*fc_table, nameFc)->data->defined;
    
    bool declared = htab_find(*fc_table,nameFc)->data->declared;

    if(token.type == RIGHT_BRACKET){//To co nasleduje po epsilon
        midFc("Autobus");
        if(defined && declared){
            if(htab_find(*fc_table, nameFc)->data->input_type_len != 0){
               err = ERR_SEMANTIKA;
                return false;
            }
        }
        else{
            htab_find(*fc_table, nameFc)->data->input_type_len = 0;
        }
        #ifdef DEBUGER
        fprintf(stderr,"%d\n",(htab_find(*fc_table, nameFc)->data->input_type_len));
        #endif
        back(token);
        destToken(&token);        
        
        outFc;
        return true;
    }

    
    int pocetZanoreni = 0;
    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }
    midFc("Cus");
    //if(NULL == ts_create_item_top(*prom_table, name)){//Delam nekde jinde
    //    destToken(&token);
    //    err = ERROR_ALLOCATION; 
    //    free(name);   
    //    return false;
    //}
    bool chybAloc = false;
    if(!sem_PromDef(name, fc_table, prom_table, NIL_T, &chybAloc, false, false)){
        midFc("NEEE\n");
        if( chybAloc){
            midFc("UGH_RUBERGOD\n");
            err = ERROR_ALLOCATION; // err pro spatny identifikator
            destToken(&token);
            return false;
        }
        //sem_PromDef(token);
        
        //htab_get_data(ts_top(prom_table)->tab, token.attribute.text)->;

        //addLocalVarOnTop( tok );
        err = ERR_UNKNOVN; // err pro spatny identifikator
        destToken(&token);
        return false;
        
    }
    #ifdef DEBUGER
    fprintf(stderr, "%p ;%s; %d##########################\n", ts_find_item_top(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    

    data_t *data = htab_get_data(ts_top(*prom_table)->tab, name);

    midFc("Budeme");
    #ifdef DEBUGER
    fprintf(stderr,"table top pointer %p\n",ts_top(*prom_table) );
    fprintf(stderr, "%p ;%s;+++++++++++++++++++++++++++++\n",ts_find_item_top(*prom_table,name),name);
    strcpy(velmiMalePoleZnaku, name);
    fprintf(stderr, "%p ;%s; %d.........................\n", ts_find_item_top(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items);
    fprintf(stderr,"\n %p <= %s\n",data, name);
    #endif
    midFc("Bud");
    char* id = data->id;
    midFc("Bud");
    midFc("crash");
    createLocalVar(id);
    ReadTopTo(id);

    destToken(&token);
    next(&token, true);

    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );
    
    fprintf(stderr, "%p ;%s; %d<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    if(token.type != VAR_INIT){
        err = ERR_UNKNOVN;
        destToken(&token);
        free(name);
        name = NULL;
        return false;
    }
    midFc("ddds\n");
    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );
    
    fprintf(stderr, "%p ;%s; %d/////////////////////////////////////////\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    destToken(&token);
    next(&token, true);
    if((token.type !=  INTEGER_KW && token.type !=  STRING_KW && token.type !=  NUMBER_KW )){
        err = ERR_UNKNOVN;
        destToken(&token); 
        free(name);
        name = NULL;
        return false;
    }
    midFc("OOOOOOO\n");
    ts_find_item_top(*prom_table, name)->data->var_type = redukce(token.type);//Oprava typu
    midFc("AAAAAAAA\n");
    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );    
    fprintf(stderr, "%p ;%s; %d```````````````````````````````````````````\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    free(name);
    name = NULL;
    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );
    
    fprintf(stderr, "%p ;%s; %d¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬¬\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    if(defined && declared){
        if(pocetZanoreni >= htab_find(*fc_table,nameFc)->data->input_type_len){
            err = ERR_SEMANTIKA;
            destToken(&token); 
            return false;
        }
        if(redukce(token.type) != htab_find(*fc_table,nameFc)->data->input_type[pocetZanoreni]){
            err = ERR_SEMANTIKA;
            destToken(&token); 
            return false;
        }
    }else{
        if(!htab_add_input_type(*fc_table, nameFc, redukce(token.type))){
            err = ERROR_ALLOCATION;
            destToken(&token); 
            return false;
        }
    }
    
    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );
    
    fprintf(stderr, "%p ;%s; %dFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    

    midFc("Ok\n");
    
    chybAloc = false;
    redukce(token.type);
    bool res = sem_addInputControl(fc_table, nameFc, redukce(token.type), pocetZanoreni, &chybAloc);
    if(chybAloc){
        err = ERR_UNKNOVN;//ALOCATION
        destToken(&token); 
        return false;
    }
    if(!res){
        err = ERR_SEMANTIKA;//ERROR_SEMANTIKA; TO DO
        destToken(&token); 
        return false;
    }
    #ifdef DEBUGER
    fprintf(stderr, "%d pocetZanoreni\n",pocetZanoreni);
    #endif
    if(!ruleSeznamParam2(fc_table, prom_table, &pocetZanoreni, nameFc)){
        destToken(&token);
        return false;
    }
    midFc("TTD\n");
    #ifdef DEBUGER

    fprintf(stderr, "%d == %d;\n",htab_find(*fc_table, nameFc)->data->input_type_len,pocetZanoreni);
    fprintf(stderr, "%d;\n",htab_find(*fc_table, nameFc)->data->input_type[0]);
    #endif
    if(htab_find(*fc_table, nameFc)->data->input_type_len != pocetZanoreni){
        err = ERR_SEMANTIKA;
        return false;
    }
    ReadTopTo(id);
    //Tady asi bude semanticka akce TO DO
    //Bude potrebovat inf, z seznam Param a ret
    #ifdef DEBUGER
    fprintf(stderr, "table pointer %p\n",  ts_top(*prom_table) );
    
    fprintf(stderr, "%p ;%s; %d£££££££££££££££££££££££££££££££\n", ts_find_item(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );
    #endif
    
    midFc("OOP\n");
    destToken(&token);
    outFc;
    return true;
}

bool ruleSeznamParam2( htab_t** fc_table, tsStack_t** prom_table, int* pocetZanoreni, char* nameFc){
    *pocetZanoreni = (*pocetZanoreni) + 1;
    inFc;
    #ifdef DEBUGER
    fprintf(stderr, "H %d pocetZanoreni V seznam2\n",*pocetZanoreni);
    #endif
    token_t token;
    next(&token, true);
    if(token.type == RIGHT_BRACKET){//To co nasleduje po epsilon
        //Konec rekurze semanticka akce?
        back(token);
        outFc;
        destToken(&token);
        return true;
    }
    midFc("uvnitr");
    if(token.type != COMMA){
        err = ERR_UNKNOVN; // err chyba synt? Nebude detekovano za vys?
        back(token);
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);

    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }

    
    destToken(&token);
    next(&token, true);
    
    if(token.type != VAR_INIT){
        err = ERR_UNKNOVN; 
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if((token.type !=  INTEGER_KW && token.type !=  STRING_KW && token.type !=  NUMBER_KW )){
        err = ERR_UNKNOVN; 
        destToken(&token);
        return false;
    }
    bool defined = htab_find(*fc_table,nameFc)->data->defined;
    bool declared = htab_find(*fc_table,nameFc)->data->declared;
    if(defined && declared){
        if(*pocetZanoreni >= htab_find(*fc_table,nameFc)->data->input_type_len){
            err = ERR_SEMANTIKA;
            destToken(&token); 
            return false;
        }
        if(redukce(token.type) != htab_find(*fc_table,nameFc)->data->input_type[*pocetZanoreni]){
            err = ERR_SEMANTIKA;
            destToken(&token); 
            return false;
        }
    }else{
        if(OK_CHAR_APP != htab_add_input_type(*fc_table, nameFc, redukce(token.type))){
            err = ERROR_ALLOCATION;
            return false;
        }
    }
    bool chybaPameti = false;
    if(!sem_PromDef(name, fc_table, prom_table,redukce(token.type), &chybaPameti,false,false)){
        if(chybaPameti){
            err = ERROR_ALLOCATION; // err pro spatny identifikator
            destToken(&token);
            return false;    
        }
        err = ERR_UNKNOVN; // err pro spatny identifikator
        destToken(&token);
        return false;
    }

    char* id = htab_get_data(ts_top(*prom_table)->tab, name)->id;
    free(name);
    name = NULL;

    createLocalVar(id);

    bool chybAloc = false;
    bool res = sem_addInputControl(fc_table, nameFc, redukce(token.type), *pocetZanoreni, &chybAloc);
    if(chybAloc){
        err = ERROR_ALLOCATION;
        destToken(&token); 
        return false;
    }
    if(!res){
        err = ERR_UNKNOVN;//ERROR_SEMANTIKA; TO DO
        destToken(&token); 
        return false;
    }

    if(!ruleSeznamParam2(fc_table, prom_table, pocetZanoreni, nameFc)){
        destToken(&token);
        return false;
    }
    ReadTopTo(id);
    //Tady asi bude semanticka akce TO DO
    //Bude potrebovat inf, z seznam Param a ret
    //ReadTopTo(/*NÁZEV - id proměnné*/); //není v tokenu
    
    outFc;
    destToken(&token);
    return true;
    
}

bool ruleSeznamRet( htab_t** fc_table, tsStack_t** prom_table, char* jmFc){
    inFc;
    token_t token;
    htabItem_t* item = htab_find(*fc_table, jmFc);
    if(item == NULL){
        err = ERR_UNKNOVN;//Sem bych se nemel dostat 
        return false;
    }
    next(&token, true);
    if((token.type !=  INTEGER_KW && token.type != STRING_KW && token.type !=  NUMBER_KW )){
        back(token);
        destToken(&token);
        
        if(item->data->output_type_len != 0){
            err = ERR_SEMANTIKA; 
            return false;
        }
        return true;
    }
    int zanoreni = 0;
    bool chybaAlok = false;
    bool ret = sem_addOutputControl(fc_table, jmFc, redukce(token.type), zanoreni, &chybaAlok);
    if(chybaAlok){
        destToken(&token);
        err = ERR_UNKNOVN;//ALLOCAT
        return false;    
    }
    if(!ret){
        destToken(&token);
        err = ERR_SEMANTIKA;//ALLOCAT
        return false;
    }

/*htabItem_t* item = htab_find(fc_table, jmFc);
    if(item == NULL){
        err = ERR_UNKNOVN;//Sem bych se nemel dostat 
        return false;
    }*/

    bool ans = ruleSeznamRet2(fc_table, prom_table, jmFc , &zanoreni);
    //Semanticka akce?
    outFc;
    destToken(&token);

    if(zanoreni != item->data->output_type_len){
        err = ERR_SEMANTIKA;
        return false;
    }
    return ans;
    
}

bool ruleSeznamRet2( htab_t** fc_table, tsStack_t** prom_table, char* jmFc, int *zanoreni){
    *zanoreni = *zanoreni + 1;
    inFc;
    token_t token;
    next(&token, true);
    if((token.type != COMMA)){
        back(token);//Konec rekurze
        destToken(&token);
        return true;
    }
    destToken(&token);
    next(&token, true);
    if((token.type !=  INTEGER_KW && token.type !=  STRING_KW && token.type !=  NUMBER_KW )){
        destToken(&token);

        return false;
    }
    bool chybaAlok = false;
    bool ret = sem_addOutputControl(fc_table, jmFc, redukce(token.type), *zanoreni, &chybaAlok);
    if(chybaAlok){
        destToken(&token);
        err = ERR_UNKNOVN;//ALLOCAT
        return false;    
    }
    if(!ret){
        destToken(&token);
        err = ERR_SEMANTIKA;
        return false;
    }


    bool ans = ruleSeznamRet2(fc_table, prom_table, jmFc , zanoreni);
    //Semanticka akce?
    outFc;
    destToken(&token);
    return ans;
}

bool rulePrirazovane( htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typZas, int pocet){

    inFc;
    token_t token;
    next(&token, true);
    back(token);
    if(sem_isFC(token, fc_table, prom_table)){
        
        int delka = appCharLen(token.attribute) + 1;
        char* name = malloc(delka);
        name[0] = '\0';
        if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
            destToken(&token);
            err = ERROR_ALLOCATION; 
            free(name);   
            return false;
        }
    
        if(!ruleVolaniFc(fc_table, prom_table)){
            destToken(&token);
            free(name);
            return false;
        }
        int navracenych = htab_get_data(*fc_table, name)->output_type_len;

        if(pocet > navracenych){
            err = ERR_UNKNOVN;
            return false;
        }
        for(int i = 0; i < navracenych ; i++){
            if(i < pocet){

                if(OK_CHAR_APP == typZas_push(typZas, htab_get_data(*fc_table, name)->output_type[i])){
                    err = ERROR_ALLOCATION;
                    return false;
                }
            }
            else{
                ReadTop();
            }
        }
        free(name);
        ////int i = 0;
        ////for(i = 0; (!typZas_isEmpty(typZas)) && htab_get_data(fc_table, name)->input_type_len > i; i++){
        ////    type_t akt = htab_get_data(fc_table, name)->output_type[i];
        ////    if(akt != typZas->typ){
        ////        if(typZas->typ != NUMBER_T || INTEGER_T != akt){
        ////            err = ERR_SEMANTIKA;
        ////            return false;
        ////        }
        ////        int2floats();
        ////    }
        ////    typZas_pop(typZas);
        ////}
        ////if(i != htab_get_data(fc_table, name)->input_type_len)
        //for (i = pocet return ; i > pocet prirazeni; i--)
        
        //trashStack();
        //TO DO dodelat trashovani prebytecneho 
        //semantika a volani fc
        destToken(&token);
        //free(name);
        return true;
    }else{
        type_t type;
        int zanoreni = 0;
        if(!ruleHodnotaR(fc_table, prom_table, &type)){
            destToken(&token);
            return false;
        }
        if(zanoreni < pocet){
            if(OK_CHAR_APP == typZas_push(typZas, type)){
                err = ERROR_ALLOCATION;
                return false;
            }
        }
        else{
            ReadTop();
        }
        if(!rulePrirazovane2(fc_table, prom_table, typZas, pocet, &zanoreni)){
            destToken(&token);
            //destToken(&token);
            return false;
        }
        if(zanoreni < pocet){
            err = ERR_SEMANTIKA;
            destToken(&token);
            return false;
        }
        //semanticka akce bude tady
        outFc;
        destToken(&token);
        return true;
    }
}
bool rulePrirazovane2(htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typZas, int pocet, int* zanoreni){
    *zanoreni = *zanoreni + 1;
    inFc;
    token_t token;
    type_t type;
    next(&token, true);
    if(token.type != COMMA){
        back(token);
        //konec rekurze
        destToken(&token);
        return true;
    }
    //NEnext(&token, true);
    if(!ruleHodnotaR(fc_table, prom_table, &type)){
        destToken(&token);
        return false;
    }
    if(*zanoreni < pocet){
        if(OK_CHAR_APP == typZas_push(typZas, type)){
            err = ERROR_ALLOCATION;
            destToken(&token);
            return false;
        }
    }
    else{
        ReadTop();
    }

    if(!rulePrirazovane2(fc_table, prom_table, typZas, pocet, zanoreni)){
        destToken(&token);
        return false;
    }
    //semanticka akce bude tady
    outFc;
    destToken(&token);
    return true;
    
}

bool ruleHodnotaR( htab_t** fc_table, tsStack_t** prom_table, type_t *vysledny){

    inFc;
    outFc;
    return specVyrazMain(fc_table, prom_table, vysledny);

/*
*/}

bool rulePrirazeni( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    /*if(!token.type == ID){
        case INTEGER:
        case NUMBER
        case STRING_IN_QUOTATION:

        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }*/
    /*if(!ruleHodnotaR()){
        err = ERR_UNKNOVN;
        //destToken(&token);
        return false;
    }*/
    if(!sem_isProm(token, fc_table, prom_table)){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }

    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }
    char* id = htab_get_data(ts_top(*prom_table)->tab, name)->id;

    //createLocalVar(id);
    int pocet = 0;
    t_typeZas zasTypu;
    typZas_init(&zasTypu);
    //if( ERR_OK != typZas_push(&zasTypu, redukce(ts_find_item(*prom_table), name)->data->var_type)){
    //    destToken(&token);
    //    free(name);
    //    name = NULL;
    //    err = ERROR_ALLOCATION;
    //    return false;
    //}

    if(!ruleZbPrirazeni(fc_table, prom_table, &zasTypu, pocet)){
        destToken(&token);
        free(name);
        name = NULL;
        return false;
    }

    if(!typZas_isEmpty(&zasTypu)){
        err = ERR_SEMANTIKA;
        free(name);
        name = NULL;
        destToken(&token);    
        return false;
    }
    type_t vraci = typZas_pop(&zasTypu); 
    type_t typ = ts_find_item(*prom_table, name)->data->var_type; 
    if(typ != vraci ){
        if(vraci == INTEGER_T && typ == NUMBER_T){
            int2floats();
        }
        else{
            err = ERR_SEMANTIKA;
            free(name);
            name = NULL;
            destToken(&token);    
            return false;
        }
    }

    ReadTopTo(id);
    

    outFc;
    destToken(&token);
    free(name);
    name = NULL;
    return true;
    
}

bool ruleZbPrirazeni(htab_t** fc_table, tsStack_t** prom_table, t_typeZas* typeZas, int pocet){
    inFc;
    pocet = pocet + 1;
    token_t token;
    next(&token, true);
    if(token.type == ASSIGN){
        //za rovna se
        if( !rulePrirazovane(fc_table, prom_table, typeZas, pocet)){
            destToken(&token);
            return false;
        }
        //konec rekurze
        destToken(&token);
        return true; 
    }else if(token.type != COMMA){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);

    /*if(!ruleHodnotaR()){
        err = ERR_UNKNOVN;
        //destToken(&token);
        return false;
    }*/
    /*if(!token.type == ID){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }*/
    if(!sem_isProm(token, fc_table, prom_table)){
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }

    if(OK_CHAR_APP != typZas_push(typeZas, ts_find_item(*prom_table, name)->data->var_type)){
        destToken(&token);
        free(name);
        name = NULL;
        err = ERROR_ALLOCATION;
        return false;
    }

    char* id = htab_get_data(ts_top(*prom_table)->tab, name)->id;
    
    
    if(!ruleZbPrirazeni(fc_table, prom_table, typeZas, pocet)){
        destToken(&token);
        return false;
    }


    if(!typZas_isEmpty(typeZas)){
        err = ERR_SEMANTIKA;
        free(name);
        name = NULL;
        destToken(&token);    
        return false;
    }
    type_t vraci = typZas_pop(typeZas); 
    type_t typ = ts_find_item(*prom_table, name)->data->var_type; 
    if(typ != vraci ){
        if(vraci == INTEGER_T && typ == NUMBER_T){
            int2floats();
        }
        else{
            err = ERR_SEMANTIKA;
            free(name);
            name = NULL;
            destToken(&token);    
            return false;
        }
    }
    //ReadTopTo(/*varName*/);
    free(name);
    name = NULL;
    outFc;
    ReadTopTo(id);
    destToken(&token);
    return true;
    
}

bool ruleIf_cons( htab_t** fc_table, tsStack_t** prom_table,char *nameFc){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type == IF_KW){
        err = ERR_UNKNOVN;
        //Sem bych se nemel dostat
        destToken(&token);
        return false;
    }

    if(!ruleVyraz(fc_table, prom_table) ){
        destToken(&token);
        return false;
    }
    int podemnou = get_itemcount_bellow(*prom_table) +  get_itemcount_top(*prom_table);
    generateIf(unikat, podemnou); //čeká dva parametry -> unikátní číslo nthIf a po kam přesouvat z LF na TF
    ts_push_fresh(*prom_table);
    
    destToken(&token);
    next(&token, true);
    if(token.type != THEN_KW){
        err = ERR_UNKNOVN; //BAD_SINTAX
        destToken(&token);
        return false;
    }
    if(ruleSlozenyPrikaz(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type == ELSE_KW){
        err = ERR_UNKNOVN; //BAD_SINTAX
        destToken(&token);
        return false;
    }
    generateElse(unikat,podemnou); //čeká dva parametry -> unikátní číslo nthIf a po kam přesouvat z LF na TF
    if(ruleSlozenyPrikaz(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type == END_KW){
        err = ERR_UNKNOVN; //BAD_SINTAX
        destToken(&token);
        return false;
    }
    
    generateIfEnd(unikat++,podemnou);//čeká dva parametry -> unikátní číslo nthIf a po kam přesouvat z LF na TF
    ts_pop(*prom_table);
    outFc;
    destToken(&token);
    return true;
    
}


bool ruleWhile(htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type == WHILE_KW){
        err = ERR_UNKNOVN;
        //Sem bych se nemel dostat
        destToken(&token);
        return false;
    }
    generateWhileLabel(unikat); //čeká Nth label (unikátní číslo)
    int pocet_na = get_itemcount_bellow(*prom_table) +  get_itemcount_top(*prom_table);
    ts_push_fresh(*prom_table);
    
    if(! ruleVyraz(fc_table, prom_table) ){
        destToken(&token);
        return false;
    }
    generateWhile(unikat, pocet_na); //čeká unikátní číslo a po kam přesouvat rámce //toNumber
    destToken(&token);
    next(&token, true);
    if(token.type != DO_KW){
        err = ERR_UNKNOVN; //BAD_SINTAX
        destToken(&token);
        return false;
    }
    if(ruleSlozenyPrikaz(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type == END_KW){
        err = ERR_UNKNOVN; //BAD_SINTAX
        destToken(&token);
        return false;
    }
    ts_pop(*prom_table);
    generateWhileEnd(unikat++,  pocet_na); //opět čeká dva parametry (na vynořování se z cyklu)
    outFc;
    destToken(&token);
    return true;
}

//pomocne fc, jelikoz nacpat to vse do jedne by uz bylo opravdu prliz
bool dalsiPomocZavorky( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true); 
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }
    destToken(&token);
    outFc;
    return true;

}
bool dalsiWrite( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    if(!ruleParVolC(fc_table, prom_table)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}
bool ruleParVolC( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;

    next(&token, true);
    if(token.type == RIGHT_BRACKET){//Epsilon
        back(token);
        destToken(&token);
        return true;
    }
    type_t bin;
    if(!ruleHodnotaR(fc_table, prom_table, &bin)){
        midFc("JOUU");
        
        destToken(&token);
        return false;
    }
    midFc("OUU");

    BuiltIn_WriteBegin();
    BuiltIn_WriteInsert();
    


    if(!ruleParVol2C(fc_table, prom_table)){
        destToken(&token);
        return false;
    }
    BuiltIn_WriteEnd();
    outFc;
    destToken(&token);
    return true;
}

bool ruleParVol2C( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type == RIGHT_BRACKET){//Epsilon
        back(token);
        destToken(&token);
        return true;
    }
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    type_t bin;
    if(!ruleHodnotaR(fc_table, prom_table, &bin)){
        destToken(&token);
        return false;
    }
    BuiltIn_WriteInsert();
    if(!ruleParVol2C(fc_table, prom_table)){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}
bool dalsiTointiger( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    type_t typ;
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != INTEGER_T){
        if(typ == NUMBER_T){
            int2floats();
        }
        else{
            err = ERR_SEMANTIKA;
            destToken(&token);
            return false;
        }
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }

    outFc;
    destToken(&token);
    functionCall("toInteger");
    return true;
}
bool dalsiSubstr( htab_t** fc_table, tsStack_t** prom_table){//Zde se uz mozna vyplati ciklus
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    type_t typ;
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != STRING_T){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != STRING_T){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != STRING_T){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }
    //programFunctionCall
    programFunctionCall("substr");
    outFc;
    destToken(&token);
    return true;
}
bool dalsiOrd( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    type_t typ;
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != STRING_T){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    if(!ruleHodnotaR(fc_table, prom_table, &typ)){
        destToken(&token);
        return false;
    }
    if(typ != STRING_T){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }
    functionCall("ord");
    outFc;
    destToken(&token);
    return true;
}
/* Nevyuzito?
bool dalsiChr( htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        destToken(&token);
        return false;
    }
    if(!ruleHodnotaR(fc_table, prom_table, &)){
        destToken(&token);
        return false;
    }
    destToken(&token);
    next(&token, true);
    if(token.type != RIGHT_BRACKET){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}*/
//konec pomocnych fc

bool ruleVolaniFc(htab_t** fc_table, tsStack_t** prom_table){
    inFc;
    token_t token;
    next(&token, true);
    switch(token.type){
        case READI_KW:
            if(!dalsiPomocZavorky(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                functionCall("readi");
                return false;
            }
            return true;
        case READN_KW:
            if(!dalsiPomocZavorky(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                functionCall("readn");
                return false;
            }
            return true;
        case READS_KW:
            if(!dalsiPomocZavorky(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                functionCall("reads");
                return false;
            }
            return true;
        case WRITE_KW:
            if (!dalsiWrite(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                return false;
            }
            destToken(&token);
            return true;
        case SUBSTR_KW:
            if (!dalsiSubstr(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                return false;
            }
            destToken(&token);
            return true;
        case ORD_KW:
            if (!dalsiOrd(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                return false;
            }
            destToken(&token);
            return true;
        case TOINTEGER_KW:
            if (!dalsiTointiger(fc_table, prom_table)){
                err = ERR_SEMANTIKA;
                destToken(&token);
                return false;
            }
            outFc;
            destToken(&token);
            return true;
    }
    if(!sem_isFC(token, fc_table, prom_table)){
        //sem bych se nemel nikdy dostat
        err = ERR_UNKNOVN;
        destToken(&token);
        return false;
    }
    
    int delka = appCharLen(token.attribute) + 1;
    char* name = malloc(delka);
    name[0] = '\0';
    if(name == NULL || appCharToStr(name, delka, token.attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
        destToken(&token);
        err = ERROR_ALLOCATION; 
        free(name);   
        return false;
    }

    destToken(&token);
    
    next(&token, true);
    if(token.type != LEFT_BRACKET){
        err = ERR_SEMANTIKA;
        destToken(&token);
        //destToken(&token);
        return false;
    }
    if(!ruleParVol(fc_table, prom_table, name)){
        //destToken(&token2);
        destToken(&token);
        return false;
    }

    destToken(&token);//Asi to tu chybelo
    next(&token, true);
    
    if(token.type != RIGHT_BRACKET){
        err = ERR_SEMANTIKA;
        //destToken(&token2);
        destToken(&token);
        return false;
    }
    
    
    functionCall(name);
    free(name);
    name = NULL;
    
    outFc;
    //destToken(&token2);
    destToken(&token);
    return true;
}

bool ruleParVol(htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    token_t token;
    type_t typOut;
    next(&token, true);
    if(token.type == RIGHT_BRACKET){//Epsilon
        back(token);
        destToken(&token);
        if (0 != htab_get_data(*fc_table, nameFc)->output_type_len){
            err = ERR_SEMANTIKA;
            return false;
        }
        return true;
    }
    back(token);
    if(!ruleHodnotaR(fc_table, prom_table, &typOut)){
        destToken(&token);
        return false;
    }
    int zanoreni = 0;
    
    if( !(htab_get_data(*fc_table, nameFc)->output_type_len < zanoreni)){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }

    if(typOut != (htab_get_data(*fc_table, nameFc)->output_type[zanoreni])){
        if (typOut != INTEGER_T && (htab_get_data(*fc_table, nameFc)->output_type[zanoreni]) != NUMBER_T)
        {
            destToken(&token);
            err == ERR_SEMANTIKA;
            return false;
        }
        int2floats();
    }


    if(!ruleParVol2(fc_table, prom_table, nameFc, &zanoreni)){
        destToken(&token);
        return false;
    }
    
    if (zanoreni != htab_get_data(*fc_table, nameFc)->output_type_len){
        destToken(&token);
        err == ERR_SEMANTIKA;
        return false;
    }

    outFc;
    destToken(&token);
    
    
    return true;
}

bool ruleParVol2(htab_t** fc_table, tsStack_t** prom_table, char* nameFc, int* zanoreni){
    inFc;
    *zanoreni = *zanoreni + 1;
    token_t token;
    next(&token, true);
    type_t typOut;

    if(token.type == RIGHT_BRACKET){//Epsilon
        back(token);
        destToken(&token);
        return true;
    }
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    
    if( !(htab_get_data(*fc_table, nameFc)->output_type_len < *zanoreni)){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }

    if(!ruleHodnotaR(fc_table, prom_table, &typOut)){
        destToken(&token);
        return false;
    }
    if(typOut != (htab_get_data(*fc_table, nameFc)->output_type[*zanoreni])){
        if (typOut != INTEGER_T && (htab_get_data(*fc_table, nameFc)->output_type[*zanoreni]) != NUMBER_T)
        {
            err == ERR_SEMANTIKA;
            return false;
        }
        int2floats();
    }

    if(!ruleParVol2(fc_table, prom_table, nameFc, zanoreni)){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}

bool ruleReturn( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    token_t token;
    next(&token, true);
    if(token.type != RETURN_KW){//Epsilon
        err = ERR_UNKNOVN; //sem bych se nemel nikdy dostat
        destToken(&token);
        return false;
    }
    if(!ruleReturnVal(fc_table, prom_table, nameFc)){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}
bool ruleReturnVal( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    token_t token;
    int zanoreni = 0;
    next(&token, true);
    type_t vysledny;
    if(token.type == END_KW){//Jedine co muze nasledovat return a neni prikaz -- prikaz zadani neosetruje, ja ho beru jako chybu
        destToken(&token);
        return true;
    }
    back;
    if(!ruleHodnotaR(fc_table, prom_table, &vysledny)){
        destToken(&token);
        return false;
    }
     
    if(!sem_checkReturn(fc_table, nameFc, vysledny, zanoreni)){
        err = ERR_SEMANTIKA;
        return false;
    }

    if(!ruleReturnVal2(fc_table, prom_table, nameFc, &zanoreni)){
        destToken(&token);
        return false;
    }
    for(; zanoreni < htab_get_data(*fc_table, nameFc)->output_type_len; zanoreni++){//Doplni chybejici nilama
        AddNilOnTop();
    }
    outFc;
    destToken(&token);
    return true;
}
bool ruleReturnVal2( htab_t** fc_table, tsStack_t** prom_table, char* nameFc, int *zanoreni){
    *zanoreni = (*zanoreni) + 1;
    inFc;
    token_t token;
    type_t vysledny;
    next(&token, true);
    if(token.type == END_KW){//Jedine co muze nasledovat return a neni prikaz -- prikaz zadani neosetruje, ja ho beru jako chybu
        
        destToken(&token);
        return true;
    }
    if(token.type != COMMA){
        err = ERR_SEMANTIKA;
        destToken(&token);
        return false;
    }
    if(!ruleHodnotaR(fc_table, prom_table, &vysledny)){
        destToken(&token);
        return false;
    }
    if(!sem_checkReturn(fc_table, nameFc, vysledny, *zanoreni)){
        err = ERR_SEMANTIKA;
        return false;
    }

    if(!ruleReturnVal2(fc_table, prom_table, nameFc, zanoreni)){
        destToken(&token);
        return false;
    }
    outFc;
    destToken(&token);
    return true;
}
bool ruleSlozenyPrikaz( htab_t** fc_table, tsStack_t** prom_table, char* nameFc){
    inFc;
    #ifdef DEBUGER

    fprintf(stderr, "%p ;%s; %d------------------------\n", ts_find_item_top(*prom_table,velmiMalePoleZnaku),velmiMalePoleZnaku, ts_top(*prom_table)->current_items );

    fprintf(stderr,"table top pointer %p\n",ts_top(*prom_table) );
    #endif
    token_t token;
    next(&token, true);
    back(token);
    bool result = false;
    midFc("CLion");
    switch (token.type){//TO DO if while tvorba prom, return
        case ID: //case INTEGER: case NUMBER: case STRING_IN_QUOTATION: CO to tu dela? tady by to delalo bordel
            midFc("ID");
            if(sem_isProm(token, fc_table, prom_table)){

                result = rulePrirazeni(fc_table, prom_table);
                break;
            }
            if(!sem_isFC(token, fc_table, prom_table)){
                result = false;
                clearStack();
    
                break;
            }
            //Zde opravdu neni break, program ma pokracovat stejnym kodem jako je pod nim
            //NE break
        case READI_KW: //NE break
        case READN_KW: //NE break
        case READS_KW: //NE break
        case WRITE_KW: //NE break
        case SUBSTR_KW://NE break
        case ORD_KW:   //NE break
        case TOINTEGER_KW: // Zde je vic case za sebou na jeden zpusob reseni
            midFc("Mnogo");
            //Tady asi nebude semanticka akce TO DO
            result = ruleVolaniFc(fc_table, prom_table);
            clearStack();
            break;
         
        case IF_KW:
            midFc("IF");
            result = ruleIf_cons(fc_table, prom_table, nameFc);
            break;
        case WHILE_KW:
            midFc("WHILE");
            result = ruleWhile(fc_table, prom_table, nameFc);
            break;
        case LOCAL_KW:
            midFc("LOCAL");
            midFc("Lion king.");
            result = ruleDecleProm(fc_table, prom_table);//TODO
            break;
        case RETURN_KW:
            midFc("RETURN");
            result = ruleReturn(fc_table, prom_table, nameFc);
            break;
        case END_KW://Jediny pripad pro Epsilon pravidlo
            midFc("END");
            //result = true;
            destToken(&token);
            outFc;
            return true;//konec rekurze
            break;//Konec vstupu
        default: //Chybny vstup --> chyba
            midFc("DEFAULT");
            midFc(token.attribute.text);
            #ifdef DEBUGER

            fprintf(stderr, "Typ %d\n", token.type);
            
            #endif
            err = ERR_UNKNOVN;
            result = false;
            break;
    }

    if(!result){
        destToken(&token);
        outFc;
        return result;
    }
    //Zde bude semantika
    if(!ruleSlozenyPrikaz(fc_table, prom_table, nameFc)){
        destToken(&token);
        outFc;
        return false;
    }
    
    outFc;
    destToken(&token);
    return true;
    
}


bool ruleVyraz(htab_t** fc_table, tsStack_t** prom_table, type_t* typ){
    //fprintf(stderr,"Vyraz\n");
    bool res = specVyrazMain(fc_table, prom_table, typ);
    return res;
}

//Provadi syntaktickou analyzu a ridi zbytek
int syntaktick_main(){
    inFc;
    
    htab_t help1; 
    tsStack_t help2;
    htab_t* help3 = &help1;
    tsStack_t* help4 = &help2;
    htab_t** fc_table = &help3;
    tsStack_t** prom_table = &help4;
    sem_init(fc_table, prom_table);

    intiToken(&tokenGlobal);
    //bool end = false;
    bool res = ruleS(fc_table, prom_table);
    destToken(&tokenGlobal);

    sem_destroy(fc_table, prom_table);
    outFc;
    return err; //TO DO nastavit err enum spravne
}

int main(){
    
    return syntaktick_main();
}




//zpracovani vyrazu
//semantika? TO DO
//Dava na zasobnik
bool operace2noStr(t_typeZas* zas){
    type_t typNahore;
    type_t typDole;
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typNahore = typZas_pop(zas);
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typDole = typZas_pop(zas);
    
    if(typDole == NUMBER_T && typNahore == NUMBER_T){
        typZas_push(zas, NUMBER_T);
        return true;
    }
    if(typDole == INTEGER_T && typNahore == NUMBER_T){
        int2floats2();
        typZas_push(zas, NUMBER_T);
        return true;
    }
    if(typDole == NUMBER_T && typNahore == INTEGER_T){
        int2floats();
        typZas_push(zas, NUMBER_T);
        return true;
    }
    if(typDole == INTEGER_T && typNahore == INTEGER_T){
        typZas_push(zas, INTEGER_T);
        return true;
    }
    err = ERR_SEMANTIKA;
    return true;    
}
bool operace2noNil(t_typeZas* zas){
    type_t typNahore;
    type_t typDole;
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typNahore = typZas_pop(zas);
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typDole = typZas_pop(zas);
    if(typDole == NIL_T || typNahore == NIL_T){
        err = ERR_SEMANTIKA;
        return false;
    }
    if(typDole != typNahore){
        if(typDole == NUMBER_T && typNahore == INTEGER_T){
            int2floats();
        }
        else if(typNahore == NUMBER_T && typDole == INTEGER_T){
            int2floats();
        }else{
            err = ERR_SEMANTIKA;
            return false;
        }
    }
    return true;
}
bool operace2(t_typeZas* zas){
    type_t typNahore;
    type_t typDole;
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typNahore = typZas_pop(zas);
    if(typZas_isEmpty(zas)){
        err = ERR_SEMANTIKA;
        return false;
    }
    typDole = typZas_pop(zas);
    if(typDole == NIL_T || typNahore == NIL_T){
        return true;
    }
    if(typDole != typNahore){
        if(typDole == NUMBER_T && typNahore == INTEGER_T){
            int2floats();
        }
        else if(typNahore == NUMBER_T && typDole == INTEGER_T){
            int2floats();
        }else{
            err = ERR_SEMANTIKA;
            return false;
        }
    }
    return true;
}


bool specVyrazMain(htab_t** fc_table, tsStack_t** prom_table, type_t* vysledny){//to do stavy chyba --> prepni vstup na epsilon
    bool end = false;
    token_t tokenN;
    token_t tokenZ;//Nikdy nevracet na vstup
    t_zasob zas;
    zas_init(&zas);
    //tokenN.type = END;
    //zas_push(&zas, tokenN)
    t_typeZas typyZas;
    typZas_init(&typyZas);
    
    bool nacitat = true;
    //Typova kontrola prijde se semantikou, bude symulovat stack
   
    while(!end){
        midFc( "iterace");
        //NE inicializuje next Zde je treba token inicializovat TO DO
        
        if(nacitat){
            next(&tokenN, true);
            back(tokenN);//Pro odstraneni tokenu ze vstupu je treba podruhe precist;
            if(tokenN.type == ID){
                if(!sem_isProm(tokenN,  fc_table, prom_table)){//neni li promena, tak konci
                    midFc("NotANumber");
                    tokenN.type = END;
                }
            }
        }
        else{
            // inicializovat? Ne, neporusil jsem zapouzdreni?
            tokenN.type = END;
        }
        if(ERROR_PODTECENI == zas_top(&zas, &tokenZ)){//Opravit aby hledal pred < nebo upravit alg.?
            tokenZ.type = END;//TOto by se nemelo redukovat
        }
        t_RizeniVyrazu dale = vyberReseni(tokenZ, tokenN);
        token_t* tmp;
        token_t* likvidovany;
        midFc( tokenZ.attribute.text);
        midFc( tokenN.attribute.text);
        #ifdef DEBUGER
        fprintf(stderr, "%d\n",dale);
        #endif
        switch(dale){
            case ROVNASE:
                
                zas_pop(&zas, tmp);
                
                destToken(tmp);
                
                destToken(&tokenN);
                
                //inicializace tokenu nyni dela next
                next(&tokenN, true);//Cisteni back
                destToken(&tokenN);

                break;
            case ADD:
                zas_push(&zas, tokenN);
                break;
            case REDUKCE:
                //TO DO tady bude semantika
                
                
                
                
                zas_top(&zas,likvidovany);
                int size = appCharLen(likvidovany->attribute) + 1;
                char*  name = malloc(size);
                name[0] = '\0';
                if(name == NULL || appCharToStr(name,size, likvidovany->attribute) != OK_CHAR_APP){//zkratkove vyhodnoceni je li nul tak neprirazuji
                    destToken(tmp);
                    destToken(likvidovany);
                    err = ERROR_ALLOCATION; 
                    free(name);   
                    return false;
                }
                //appCharToStr(name,size, likvidovany);
                type_t typNahore;
                type_t typDole;
                switch(likvidovany->type){//TO DO typova kontrola   
                    case EQUAL:
                        if(!operace2(&typyZas)){
                            return false;
                        }
                        stackTopEqualToNext();
                        typZas_push(&typyZas, BOOL_T);
                        break; 
                    case LESS:
                        if(!operace2noNil(&typyZas)){
                            return false;
                        }
                        smaller();
                        typZas_push(&typyZas, BOOL_T);
                        break;
                    case LESS_EQ:
                        if(!operace2noNil(&typyZas)){
                            return false;
                        }
                        smallerEqual();
                        typZas_push(&typyZas, BOOL_T);
                        break;
                    case GREATER:
                        if(!operace2noNil(&typyZas)){
                            return false;
                        }
                        bigger();
                        typZas_push(&typyZas, BOOL_T);
                        break;
                    case GREATER_EQ:
                        if(!operace2noNil(&typyZas)){
                            return false;
                        }
                        biggerEqual();
                        typZas_push(&typyZas, BOOL_T);
                        break;
                    case NOT_EQUAL:
                        if(!operace2(&typyZas)){
                            return false;
                        }
                        stackTopNotEqualToNext();
                        typZas_push(&typyZas, BOOL_T);
                        break;
                    case DOUBLE_DOT:
                        if(typZas_pop(&typyZas) != STRING_T || typZas_pop(&typyZas) != STRING_T){
                            return false;
                        }
                        concatVars();
                        typZas_push(&typyZas, STRING_T);
                        break;
                    case PLUS:
                        if(!operace2noStr(&typyZas)){
                            return false;
                        }
                        StackAdds();
                        
                        break;
                    case MINUS:
                        if(!operace2noStr(&typyZas)){
                            return false;
                        }
                        StackSubs();
                        
                        break;
                    case MULTIPLY:
                        if(!operace2noStr(&typyZas)){
                            return false;
                        }
                        StackMuls();
                        
                        break;
                    case SLASH:
                        if(!operace2noStr(&typyZas)){
                            return false;
                        }//TO DO kontrola 0
                        StackDivs();
                        typZas_pop(&typyZas);
                        typZas_push(&typyZas, NUMBER_T);
                        break;
                    case DOUBLE_SLASH:
                        if(typZas_pop(&typyZas) != INTEGER_T || typZas_pop(&typyZas) != INTEGER_T){
                            err = ERR_SEMANTIKA;
                            return false;
                        }//TO DO kontrola 0
                        StackIdivs();
                        typZas_push(&typyZas, INTEGER_T);
                        break;
                    case HASH:
                        if(typZas_pop(&typyZas) != STRING_T){
                            err = ERR_SEMANTIKA;
                            return false;
                        }
                        strlenFunction();
                        typZas_push(&typyZas, BOOL_T);
                        //strlenFunction();
                        break;
                    case ID:
                        if(sem_isProm(*likvidovany, fc_table, prom_table)){//TO DO
                            //long long unsigned int cisclo = ;// get_itemcount_bellow(prom_table) +  get_itemcount_top(prom_table);
                            //char name[50];//TO DO odstranit magicke konstanty
                            //name[0] = '\0';
                            //snprintf(49, name,"%llu",cisclo);
                            addLocalVarOnTop( ts_find_item(*prom_table, name)->data->id);
                            typZas_push(&typyZas, ts_find_item(*prom_table, name)->data->var_type);//TO DO
                        }
                        break;
                    case INTEGER: 
                        addConstOnTop(name,"INTEGER");
                        typZas_push(&typyZas, INTEGER_T);
                        break;
                    case NUMBER:
                        addConstOnTop(name,"NUMBER");
                        typZas_push(&typyZas, NUMBER_T);
                        break;
                    case STRING_IN_QUOTATION:
                        typZas_push(&typyZas, STRING_T);
                        AddStringOnTop(name);
                        break;
                }
                free(name);
                zas_pop(&zas, tmp);
                destToken(tmp);
                destToken(likvidovany);
                break;
            case CHYBA:
                if(nacitat = false){
                    //vyprazdnit zasobnik
                    return false;
                }
                nacitat = false;
                destToken(&tokenN);
            case KONEC:
                if(typZas_isEmpty(&typyZas)){
                    err = ERR_SEMANTIKA;
                    return false;
                }
                *vysledny = typZas_pop(&typyZas);
                if(!typZas_isEmpty(&typyZas)){
                    err = ERR_SEMANTIKA;
                    return false;
                }
        }
        //Na zasobniku pro hodnoty je 1 hodnota, je ji treba popnout?
        //Neinicializoval jsem hodestToken(&tokenN);
        return true;
        break;
    }
}

t_RizeniVyrazu vyberReseni(token_t tokenZ, token_t tokenN){
    //Dva switche, ktere vyberou jestli budu koncit redukovat propagovat nebo rovnat
    midFc("vyber");
    #ifdef DEBUGER
    fprintf(stderr,"zas   %d # %s\nvstup %d # %s\n",(int)(tokenZ.type),tokenZ.attribute.text,(int)(tokenN.type), tokenN.attribute.text );
    #endif
    switch(tokenZ.type){
        case EQUAL: case LESS: case LESS_EQ: case GREATER:
        case NOT_EQUAL: case GREATER_EQ:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                    //Chyba
                    return CHYBA;
                    break;
                case DOUBLE_DOT: case PLUS: case MINUS: case MULTIPLY:
                case SLASH: case DOUBLE_SLASH: case HASH: case LEFT_BRACKET: 
                    return ADD;
                    //propagace
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    //redukce
                    return REDUKCE;
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION://Konec vstupu?           
                    //propagace
                    return ADD;
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    break;
                    //redukce
            }
            break;
        case DOUBLE_DOT:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                    return REDUKCE;
                    //redukce
                    break;
                case DOUBLE_DOT: case PLUS: case MINUS: case MULTIPLY:
                case SLASH: case DOUBLE_SLASH: case HASH: case LEFT_BRACKET: 
                    //propagace
                    return ADD;
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    return REDUKCE;
                    //redukce
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:
                    //Konec vstupu?           
                    //propagace
                    return ADD;
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    break;
                    //redukce
            }
            break;
        case MINUS: 
        case PLUS:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                    return REDUKCE;
                    //redukce
                    break;
                case MULTIPLY:
                case SLASH: case DOUBLE_SLASH: case HASH: case LEFT_BRACKET: 
                    return ADD;            
                    //propagace
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    //redukce
                    return REDUKCE;
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    return ADD;
                    //propagace
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    break;
                    //redukce
            }
            break;
        case MULTIPLY:
        case SLASH:
        case DOUBLE_SLASH:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH: 
                    return REDUKCE;    
                    //redukce
                    break;
                case HASH: case LEFT_BRACKET: 
                    return ADD;
                    //propagace
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    return REDUKCE;
                    //redukce
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    //propagace
                    return ADD;
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    //redukce
                    break;
            }
            break;
        case HASH:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH: 
                    return REDUKCE;
                    //redukce
                    break;
                case HASH:
                    return CHYBA;
                    //chyba 
                    break;
                case LEFT_BRACKET: 
                    return ADD;
                    //propagace
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    return REDUKCE;
                    //redukce
                    break;
                case ID:  case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    return ADD;
                    //propagace
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    //redukce
                    break;
            }
            break;
        case LEFT_BRACKET:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH:    
                case HASH:
                case LEFT_BRACKET: 
                    return ADD;
                    //propagace
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    //rovna se
                    return ROVNASE;
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    return ADD;
                    //propagace
                    break;
                default://Konec vstupu uz jiste
                    return CHYBA;
                    //chyba
            }
            break;
        case RIGHT_BRACKET:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH:    
                case HASH:
                    return REDUKCE;
                    //redukce
                    break;
                case LEFT_BRACKET: 
                    return CHYBA;
                    //konec vstupu prehodit vstup na epsilon back
                    //chyba
                    break;
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    return REDUKCE;
                    //redukce
                    break;
                case ID:  case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    return CHYBA;
                    //chyba
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    break;
                    //redukce
            }
            break; 
        case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH:    
                    return REDUKCE;
                    //redukce
                    break;
                case HASH: case LEFT_BRACKET: 
                    return CHYBA;
                    //konec vstupu prehodit vstup na epsilon back
                    //chyba
                case RIGHT_BRACKET:// Bacha je v mnozine za vyrazem //Konec vstupu
                    return REDUKCE;
                    //redukce
                    break;
                case ID: case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    return CHYBA;
                    //chyba
                    break;
                default://Konec vstupu uz jiste
                    return REDUKCE;
                    //redukce
            }
            break;
        default://Konec zasobniku
            switch(tokenN.type){
                case EQUAL: case LESS: case LESS_EQ: case GREATER:
                case GREATER_EQ: case NOT_EQUAL:
                case DOUBLE_DOT: case PLUS: case MINUS:
                case MULTIPLY: case SLASH: case DOUBLE_SLASH:    
                case HASH: case LEFT_BRACKET:
                    return REDUKCE;
                    //redukce
                    break;
                case RIGHT_BRACKET: 
                    return CHYBA;
                        //konec vstupu prehodit vstup na epsilon
                        // back uz bylo -- Zajistit se nebude prepsano epsilon
                        //chyba
                    break;
                case ID:  case INTEGER: case NUMBER: case STRING_IN_QUOTATION:  //Konec vstupu?           
                    midFc("REDUKCE");
                    return REDUKCE;
                    //redukce
                    break;
                default://Konec vstupu uz jiste
                    return KONEC;
                    //ukonceni ciklu
                }
                break;
        }
    #ifdef DEBUGER

    fprintf(stderr,"CHYBA zpracovani vyrazu, toto by mel byt mrtvi kod");
    #endif
    return KONEC;
}
//konec zpracovani vyrazu
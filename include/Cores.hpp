#ifdef _CORES

    #define RESET   "\033[m"
    #define ERRO    "\033[31m"
    #define OK      "\033[32m"
    #define MENU    "\033[1m"
    #define TELA    "\033[2J\033[H"
    #define SENHA   "\033[8m"
    #define SIM     "\033[32m"
    #define NAO     "\033[31m"

    #define COR_P_BAIXA     "\033[32m"
    #define COR_P_MEDIA     "\033[33m"
    #define COR_P_ALTA      "\033[1;31m"


#else

    #define RESET   ""
    #define ERRO    ""
    #define OK      ""
    #define MENU    ""
    #define TELA    "\n\n\n\n\n"
    #define SENHA   ""
    #define SIM     ""
    #define NAO     ""

    #define COR_P_BAIXA     ""
    #define COR_P_MEDIA     ""
    #define COR_P_ALTA      ""

#endif

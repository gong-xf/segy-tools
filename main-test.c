
#include "_header.h"

int TraceIsEmpty(float *d, int ns)
{
    int i;
    for(i=0;i<ns;i++)
    if(0!=d[i]) return 0;
    return 1;
}

int main ( int argc, char *argv[] )
{
    char info[1024];
    if(argc==1){
        printf("********************************************************************************\n");
        printf("%s imglist= gather= verb=1\n", argv[0]);
        printf("********************************************************************************\n");
        return 0;
    }
    
    int verb=1;
    char imglist[1024], gather[1024], dirgather[1024];
    strcpy ( imglist, "");
    strcpy ( gather, "");
    strcpy ( dirgather, "");
    PickInt(argc,argv,"verb",&verb,0);
    PickStr(argc,argv,"imglist",imglist,verb);
    PickStr(argc,argv,"gather",gather,verb);
    //PickStr(argc,argv,"dirgather",dirgather,verb);
    /*
    int cdpmin=-1, cdpmax=10000000;
    PickInt(argc,argv,"cdpmin",&cdpmin,verb);
    PickInt(argc,argv,"cdpmax",&cdpmax,verb);
    mkdir (dirgather, S_IRWXU);
    */
    char path_cdp[1024], path_shot[1024];
    FILE *fp;
//HEREN;
    int ns;
    int ntrall = 0;
    int shot_ntr;
    SEGY H, HH;
    segy h, hh;
    float *d, *dd;
//HEREN;
    FILE *FPIMGLIST = fopen ( imglist, "rt" );
    
    if(NULL==FPIMGLIST){
        printf("ERROR, cannot open %s\n", imglist);
        return 0;
    }
    
    FILE *FPGATHER = fopen (gather, "wb" );
    FILE *FPSHOT;
    
    int NSHOT=0;
//HEREN;
    while ( !feof(FPIMGLIST) )
    {
//HEREN;
        //fgets(path_shot, 1000, FPIMGLIST);
        fscanf ( FPIMGLIST, "%s", path_shot);
//HEREN;
        if(0!=access(path_shot,F_OK)){
            printf("warning: cannotaccess %s skip \n", path_shot );
            continue;
        }
//HEREN;
        NSHOT++;
        printf("NSHOT=%d, %s ==>  %s\n", NSHOT, path_shot, gather );
//HEREN;
        FPSHOT = fopen (  path_shot, "rb" );
        fread ( &H, sizeof(SEGY), 1, FPSHOT );
        
        if(ntrall==0){
            memcpy (&HH, &H, sizeof(SEGY) );
            ConvertSEGY(&HH);
            ns = HH.ns;
            d = (float*)malloc(sizeof(float)*ns);
            fwrite ( &H, sizeof(SEGY), 1,  FPGATHER );
        }
        
        while ( !feof(FPSHOT) ){
            fread ( &h, sizeof(segy), 1, FPSHOT);
            fread ( d, sizeof(float), ns, FPSHOT );
            fwrite ( &h, sizeof(segy), 1, FPGATHER);
            fwrite ( d, sizeof(float), ns, FPGATHER );
        }
        fclose(FPSHOT); 
    }
    fclose(FPGATHER);
    return 0;
}




    

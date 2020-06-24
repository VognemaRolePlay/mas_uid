


//			Masson`s unique indetifier System
//			This include adds the ability to get a unique identifier
//			

//			Version: 0.2
//			Last Release: 22.06.2020

//			Dependencies:
//			- No

//			Compatibility:
//			- No


#if defined MAS_UID
	#endinput
#else
	#define MAS_UID
#endif

#if !defined MAS_UID_MAX_CODES
	#define MAS_UID_MAX_CODES	32
#endif

#if !defined MAS_UID_LENGTH
	#define MAS_UID_LENGTH	16
#endif



static 
	MAS_UID_CODE[MAS_UID_MAX_CODES] = {1, 1, 1, ...},
	MAS_UID_USES;


stock GenerateUID(output[], const size = sizeof output) {
	new MAS_UID_SALT[MAS_UID_LENGTH];
	MAS_UID_GenerateSalt(MAS_UID_SALT);
	SHA256_PassHash(MAS_UID_CODE[MAS_UID_USES], MAS_UID_SALT, output, size);
	MAS_UID_USES++;
	if(MAS_UID_USES == MAS_UID_MAX_CODES) MAS_UID_USES = 0;
	return 1;
}

stock MAS_UID_GenerateSalt(output[], const size = MAS_UID_LENGTH+1) {
	new mas_uid_tmp = floatround(gettime() / MAS_UID_CODE [MAS_UID_USES]);	
	valstr(output, mas_uid_tmp);
	return 1;
}

public OnGameModeInit() {

	new mas_uid_timestamp = gettime();
	for(new i = 1; i < MAS_UID_MAX_CODES; i++) {
		MAS_UID_CODE [i] = floatround( (mas_uid_timestamp / (i * 3) + 1) );
	}

    #if defined _mas_uid_OnGameModeInit  
        _mas_uid_OnGameModeInit();
    #endif
    return 1;
}
#if    defined    _ALS_OnGameModeInit   
    #undef    OnGameModeInit
#else
    #define    _ALS_OnGameModeInit
#endif
#define    OnGameModeInit    _mas_uid_OnGameModeInit
#if    defined    _mas_uid_OnGameModeInit
forward _mas_uid_OnGameModeInit();
#endif 

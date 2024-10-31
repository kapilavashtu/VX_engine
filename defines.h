#ifndef DEFINES_H
#define DEFINES_H

#define LINQ
#define DEBUG
#define SERVER_DEBUG
#define TEST_TIMER
#define NO_TRAY

#define SET_BIT(reg, bit)         		reg |= ((uint64_t) << bit)
#define CLEAR_BIT(reg, bit)      		reg &= (~((uint64_t) 1 << bit))
#define INVERT_BIT(reg, bit)        	reg ^= ((uint64_t) 1 << bit)
#define BIT_IS_SET(reg, bit)        	((reg & ((uint64_t) 1 << bit)) != 0)
#define BIT_IS_CLEAR(reg, bit)      	((reg & ((uint64_t) 1 << bit)) == 0)

#define ETH_TX_INTERVAL         10
#define WORKER_TIMER_INTERVAL   10

#define FORM1                   0xFF00FF00FF00FF00
#define FORM2                   0xFFFF0000FFFF0000
#define FORM3                   0xFFFFFFFF00000000
#define FORM4                   0x0F0F0F0F0F0F0F0F

//RECIEVE DATA BLOCK FROM MK
#define INPUTS_OFFSET           0
#define DEVICE_OFFSET           8
#define FAULT_OFFSET            16
#define SYS_OFFSET              24
#define RX_COUNTER_OFFSET       32
#define TX_COUNTER_OFFSET       40
#define WIRE_CRC_ERROR_OFFSET   48
#define X_COUNTER_OFFSET        56

//SEND TO MK BLOCK DATA OFFSET
#define OUTPUTS_STATES_OFFSET   0
#define DEV_RUN_STATES_OFFSET   8
#define DEV_STOP_STATES_OFFSET  16
#define SYS_DATA_OFFSET         24

#define INPUTS_BLOCK_SIZE       8
#define DEVICES_BLOCK_SIZE      8
#define FAULT_BLOCK_SIZE        8
#define SYS_BLOCK_SIZE          8
#define RX_COUNTER_SIZE         8
#define TX_COUNTER_SIZE         8
#define WIRE_CRC_ERROR_SIZE     8
#define X_COUNTER_SIZE          8

//SEND TO MK BLOCK DATA OFFSET
#define OUTPUTS_STATES_OFFSET   0
#define DEV_RUN_STATES_OFFSET   8
#define DEV_STOP_STATES_OFFSET  16
#define SYS_DATA_OFFSET         24

#define OUTPUTS_STATES_BLOCK_SIZE	 8
#define DEV_RUN_STATES_BLOCK_SIZE	 8
#define DEV_STOP_STATES_BLOCK_SIZE	 8
#define SYS_DATA_BLOCK_SIZE			 8

#define START                   1
#define START_ANIM1             2
#define START_ANIM2             3
#define STOP                    4
#define RESET                   5

#define WAIT_COMMAND_FLAG				0
#define WAIT_REQUEST_FLAG				1
#define RUN_STATUS						2
#define DONE_STATUS						3
#define ACTION1_STATUS					4
#define ACTION2_STATUS					5
#define ACTION3_STATUS					6
#define ACTION4_STATUS					7

#define START_DEVICE_COMMAND    0b10101010
#define START_ANIMATRONIC_1     0b11110000
#define START_ANIMATRONIC_2     0b00001111
#define STOP_DEVICE_COMMAND     0b11001100
#define RESET_DEVICE_COMMAND    0b00111100


//*********************************
#define MAIN_WINDOW_HEIGHT      600
#define MAIN_WINDOW_WIDTH       800

#ifdef LINQ_SCREEN
#define SCREEN_FIRST_H          1920
#define SCREEN_FIRST_W          1080
#define SCREEN_SECOND_H         1600
#define SCREEN_SECOND_W         900

#define SCREEN_FIRST_AX         0
#define SCREEN_FIRST_AY         0
#define SCREEN_SECOND_AX        -1600
#define SCREEN_SECOND_AY        180
#endif

#ifdef TEST_TIMER
#define SCREEN_FIRST_H          1366
#define SCREEN_FIRST_W          768
#define SCREEN_SECOND_H         1024
#define SCREEN_SECOND_W         768

#define SCREEN_FIRST_AX         0
#define SCREEN_FIRST_AY         0
#define SCREEN_SECOND_AX        1366
#define SCREEN_SECOND_AY        0
#endif


#define SCREEN0_H               1366
#define SCREEN0_W               768

#define SCREEN0_AX              0
#define SCREEN0_AY              0

#define SCREEN1_H               1024
#define SCREEN1_W               768

#define SCREEN1_AX              1366
#define SCREEN1_AY              0

#define SOUND_TRACK_NUM         19
#define MUSIC_TRACK_NUM         8
#define VIDEO_TRACK_NUM         8

//====================================== OUTPUT ETHERNET COMMAND LIST ==========================================
#define COMMAND_START           1
#define GAME_START              2
#define KILL_GAMER              3
#define STOP_GAME               4
#define GET_STATUS              5
#define GET_DATA_BLOCK          6

#define VIDEO1_PLAYING			7
#define VIDEO1_STOPPED			8
#define VIDEO2_STOPPED			9
#define VIDEO3_STOPPED 			10
#define VIDEO5_MIN_PLAYING		11
#define VIDEO5_MIN_STOPPED		12
#define VIDEO_FAIL1_STOPPED		13
#define VIDEO_FAIL2_STOPPED 	14
#define VIDEO_WIN_STOPPED		15

#define INCREMENT_GAME_TIMER	16
#define	DECREMENT_GAME_TIMER	17

#define CHANGE_GATE_STATE		18
#define CHANGE_LED_STATE		19

#define RUN_ANIMATRONIC_1		20
#define RUN_ANIMATRONIC_2		21
#define RUN_STUK				22
#define RUN_LOUDSPEAKER			23
#define RUN_MEMORIZER			24
#define RUN_CATCH_SECOND_A		25
#define RUN_CATCH_SECOND_B		26
#define RUN_SCREAM_LED			27
#define RUN_SWITCHES			28
#define RUN_PHOTOELEMENTS		29

#define DONE_EVACUATION			30
#define DONE_SOCKETS			31
#define DONE_KEY_PANEL			32
#define DONE_HEAD				33
#define DONE_CATCH_SECOND_A		34
#define DONE_CATCH_SECOND_B		35
#define DONE_BODY_MANEKEN		36
#define DONE_TORCHLIGHTS		37
#define DONE_MEMORIZER			38
#define DONE_PHOTOELEMENTS		39
#define DONE_PUZZLE_BOX			40
#define DONE_BIG_BOX			41
#define DONE_SWITCHES			42

#define START_SMOKE_MACHINE		43
#define STOP_SMOKE_MACHINE		44
#define ON_MONITOR				45
#define OFF_MONITOR				46

//====================================== INPUT ETHERNET COMMAND LIST ==========================================
#define PLAY_SOUND 				10
#define PLAY_MUSIC 				11
#define PLAY_VIDEO				12
#define STOP_SOUND				13
#define STOP_MUSIC				14
#define STOP_VIDEO				15

#define SEND_LEVEL_STATE		20
#define SEND_LAST_DEVICE_STATE	21
#define SEND_LED_STATE			22
#define SEND_GATE_STATE			23
#define SCREAMER1_ACTION 		24
#define SCREAMER2_ACTION 		28

#define START_CAMERA			25
#define STOP_CAMERA				26

#define SEND_SERVICE_MESSAGE	27

#define PING                    88



//TABLET COMMAND
#define COMMAND_START_T           "1"
#define GAME_START_T              "2"
#define KILL_GAMER_T              "3"
#define STOP_GAME_T               "4"
#define GET_STATUS_T              "5"
#define GET_DATA_BLOCK_T          "6"


#define COMMAND 0
#define PRINT_VALUES 10

//====================================WIRE INCOMING COMMANDS==========================
//!команды полученные тт контроллеров,отображаются на массив входов


//======================================== MK0 INPUTS =================================
#define key_panel               22
#define gerkon_switches         23
#define motion_big_box          24
#define gerkon_torchlights      25
#define uv_button               27
#define gerkon_door4            28
#define gerkon_f_led            29
#define gerkon_head             30
#define gerkon_puzzle_box       31
#define gerkon_evacuation       32
#define gerkon_uv_last          37
#define motion_room4            36
#define gerkon_screamer         34
#define kill_button             35

#define motion_room2            40
#define gerkon_maneken          41

#define sockets_done            50  //address #
#define photo_done              51  //
#define switches_done           52  //
#define catch_second_a_done     53  //
#define catch_second_b_done     54  //
#define scream_done             55  //
#define memory_done             56  //

#define sockets_done_sound               57  //
#define photo_pig_action                 58  //
#define switches_done_sound              59  //
#define catch_second_a_wrong_sound       60  //
#define catch_second_b_wrong_sound       61  //
#define scream_done_sound                62  //
#define memory_done_sound                63  //




//======================================== MK1 OUTPUTS ================================
#define pneumo_loudspeaker      2
#define start_photo             3
#define room1_led               4
#define frezze_led              5
#define uv_led                  6
#define monitor_power           7
#define smoke_power_pin         8
#define uv220_light             9
#define gate_cage_door          10
#define gate_big_box_top        11
#define table_led               12
#define hope_led                13
#define start_anim1             14  //
#define start_anim2             15  //
#define start_switches          16  //
#define start_second_a          17  //
#define start_sockets           18  //
#define start_second_b          19  //

#define gate_secret_box1        22
#define secret_door_led         24
#define gate_door4              25
#define gate_secret_door        27
#define gate_secret_box2        28
#define gate_switches           29
#define gate_big_box_deck       30
#define start_scream            31
#define maneken_led             32
#define gate_puzzle_box         33
#define pneumo_coil_pig_close   34
#define gate_doll_box           35
#define pig_led                 36
#define puzzle_led              37
#define torch_led               38
#define uv_led_torch            39
#define smoke_start_pin         40
#define gate_door2              42
#define room3_led               43
#define pneumo_coil_pig_open    44
#define gate_final_door         45
#define mirror_led              46
#define doll_led                47
#define door4_led               48
#define led_kill_button         49
#define door2_led               50
#define gate_torchlights        51
#define room2_led               52
#define start_memory            54
#define pneumo_stuck_open       55
#define pneumo_stuck_close      56
#define big_box_led             57

#define PNEUMATIC               20
#define SOCKETS                 10
#define PHOTO                   11
#define SWITCHES                12
#define CATCH_SEC_A             13
#define CATCH_SEC_B             14
#define SCREAM                  15
#define MEMORY                  16

#define animatronic1_start      1
#define animatronic2_start      2

#define PROGRAM_STARTED "================================================================================================================================== \r\n Program Started:: \t"
#define PROGRAM_CLOSED  "================================================================================================================================== \r\n Program Closed:: \t"

#ifdef LINQ
#define LOG_FILE_PATH             "/home/linq/vx_dv.log_"
#define INPUTS_LOG_FILE_PATH      "/home/linq/vx_dv_inputs.log"
#define SETTINGS_PATH             "/home/linq/vx_dv_settings.ini"
#define SCREAMER_PATH             "/home/linq/Изображения/shu.jpeg"
#define MENU_IMAGE_PATH           "/home/linq/Изображения/shu.jpeg"
#endif

#ifdef URBAN
#define LOG_FILE_PATH "/home/linq/vx_dv.log"
#define INPUTS_LOG_FILE_PATH "/home/linq/vx_dv_inputs.log"
#define SETTINGS_PATH             "/home/linq/vx_dv_settings.ini"
#endif

#endif // DEFINES_H

#ifdef WINDOWS

#include "selftest_local.h"

void Test_Events() {
	// reset whole device
	SIM_ClearOBK(0);

	CMD_ExecuteCommand("clearAllHandlers", 0);
	CMD_ExecuteCommand("addEventHandler 123 5 setChannel 10 555", 0);
	SELFTEST_ASSERT_CHANNEL(10, 0);
	EventHandlers_FireEvent(123, 4);
	SELFTEST_ASSERT_CHANNEL(10, 0);
	EventHandlers_FireEvent(123, 6);
	SELFTEST_ASSERT_CHANNEL(10, 0);
	EventHandlers_FireEvent(123, 5); // matching arguments - event will fire
	SELFTEST_ASSERT_CHANNEL(10, 555);
	CMD_ExecuteCommand("clearAllHandlers", 0);
	CMD_ExecuteCommand("setchannel 10 666", 0);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent(123, 5);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	CMD_ExecuteCommand("addEventHandler2 123 5 6 setChannel 10 444", 0);
	EventHandlers_FireEvent2(123, 5, 5);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent2(123, 6, 5);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent2(123, 6, 6);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent2(123, 5, 6); // matching arguments - event will fire
	SELFTEST_ASSERT_CHANNEL(10, 444);
	CMD_ExecuteCommand("clearAllHandlers", 0);
	CMD_ExecuteCommand("setchannel 10 666", 0);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent2(123, 6, 6);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent2(123, 5, 6); // no event to fire
	SELFTEST_ASSERT_CHANNEL(10, 666);
	CMD_ExecuteCommand("addEventHandler3 123 1 2 3 setChannel 10 222", 0);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent3(123, 1, 2, 2);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent3(123, 1, 2, 1);
	SELFTEST_ASSERT_CHANNEL(10, 666);
	EventHandlers_FireEvent3(123, 1, 2, 3);
	SELFTEST_ASSERT_CHANNEL(10, 222);

	// test events parse
	SELFTEST_ASSERT(EVENT_ParseEventName("channel1") == CMD_EVENT_CHANGE_CHANNEL0 + 1);
	SELFTEST_ASSERT(EVENT_ParseEventName("channel6") == CMD_EVENT_CHANGE_CHANNEL0 + 6);
	SELFTEST_ASSERT(EVENT_ParseEventName("channel15") == CMD_EVENT_CHANGE_CHANNEL0 + 15);
	SELFTEST_ASSERT(EVENT_ParseEventName("noPingTime") == CMD_EVENT_CHANGE_NOPINGTIME);
	SELFTEST_ASSERT(EVENT_ParseEventName("NoMQTTTime") == CMD_EVENT_CHANGE_NOMQTTTIME);
	SELFTEST_ASSERT(EVENT_ParseEventName("voltage") == CMD_EVENT_CHANGE_VOLTAGE);
	SELFTEST_ASSERT(EVENT_ParseEventName("current") == CMD_EVENT_CHANGE_CURRENT);
	SELFTEST_ASSERT(EVENT_ParseEventName("power") == CMD_EVENT_CHANGE_POWER);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnRelease") == CMD_EVENT_PIN_ONRELEASE);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnPress") == CMD_EVENT_PIN_ONPRESS);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnClick") == CMD_EVENT_PIN_ONCLICK);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnToggle") == CMD_EVENT_PIN_ONTOGGLE);
	SELFTEST_ASSERT(EVENT_ParseEventName("IPChange") == CMD_EVENT_IPCHANGE);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnHold") == CMD_EVENT_PIN_ONHOLD);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnHoldStart") == CMD_EVENT_PIN_ONHOLDSTART);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnDblClick") == CMD_EVENT_PIN_ONDBLCLICK);
	SELFTEST_ASSERT(EVENT_ParseEventName("On3Click") == CMD_EVENT_PIN_ON3CLICK);
	SELFTEST_ASSERT(EVENT_ParseEventName("On4Click") == CMD_EVENT_PIN_ON4CLICK);
	SELFTEST_ASSERT(EVENT_ParseEventName("On5Click") == CMD_EVENT_PIN_ON5CLICK);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnChannelChange") == CMD_EVENT_CHANNEL_ONCHANGE);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnUART") == CMD_EVENT_ON_UART);
	SELFTEST_ASSERT(EVENT_ParseEventName("MQTTState") == CMD_EVENT_MQTT_STATE);
	SELFTEST_ASSERT(EVENT_ParseEventName("NTPState") == CMD_EVENT_NTP_STATE);
	SELFTEST_ASSERT(EVENT_ParseEventName("LEDState") == CMD_EVENT_LED_STATE);
	SELFTEST_ASSERT(EVENT_ParseEventName("LEDMode") == CMD_EVENT_LED_MODE);
	SELFTEST_ASSERT(EVENT_ParseEventName("energycounter") == CMD_EVENT_CHANGE_CONSUMPTION_TOTAL);
	SELFTEST_ASSERT(EVENT_ParseEventName("energy") == CMD_EVENT_CHANGE_CONSUMPTION_TOTAL);
	SELFTEST_ASSERT(EVENT_ParseEventName("energycounter_last_hour") == CMD_EVENT_CHANGE_CONSUMPTION_LAST_HOUR);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_RC5") == CMD_EVENT_IR_RC5);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_RC6") == CMD_EVENT_IR_RC6);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_Samsung") == CMD_EVENT_IR_SAMSUNG);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_PANASONIC") == CMD_EVENT_IR_PANASONIC);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_NEC") == CMD_EVENT_IR_NEC);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_SAMSUNG_LG") == CMD_EVENT_IR_SAMSUNG_LG);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_SHARP") == CMD_EVENT_IR_SHARP);
	SELFTEST_ASSERT(EVENT_ParseEventName("IR_SONY") == CMD_EVENT_IR_SONY);
	SELFTEST_ASSERT(EVENT_ParseEventName("WiFiState") == CMD_EVENT_WIFI_STATE);
	SELFTEST_ASSERT(EVENT_ParseEventName("TuyaMCUParsed") == CMD_EVENT_TUYAMCU_PARSED);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnADCButton") == CMD_EVENT_ADC_BUTTON);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnCustomDown") == CMD_EVENT_CUSTOM_DOWN);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnCustomUP") == CMD_EVENT_CUSTOM_UP);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnMQTT") == CMD_EVENT_ON_MQTT);
	SELFTEST_ASSERT(EVENT_ParseEventName("OnDP") == CMD_EVENT_ON_DP);

	// test for numeric strings
	SELFTEST_ASSERT(EVENT_ParseEventName("123") == 123);
	SELFTEST_ASSERT(EVENT_ParseEventName("42") == 42);

	// test for unknown event names
	SELFTEST_ASSERT(EVENT_ParseEventName("UnknownEvent") == CMD_EVENT_NONE);
	SELFTEST_ASSERT(EVENT_ParseEventName("") == CMD_EVENT_NONE);
	SELFTEST_ASSERT(EVENT_ParseEventName(" ") == CMD_EVENT_NONE);
}

void Test_UART() {
	int USED_BUFFER_SIZE = 123;
	UART_InitReceiveRingBuffer(USED_BUFFER_SIZE);
	byte next = 0;
	for (int i = 0; i < 512; i++) {
		SELFTEST_ASSERT(UART_GetDataSize() == 0);
		UART_AppendByteToReceiveRingBuffer(next);
		SELFTEST_ASSERT(UART_GetDataSize() == 1);
		byte check = UART_GetByte(0);
		SELFTEST_ASSERT(check == next);
		UART_ConsumeBytes(1);
		SELFTEST_ASSERT(UART_GetDataSize() == 0);
		next++;
	}
	for (int i = 0; i < 66; i++) {
		byte nn;
		nn = next;
		for (int j = 0; j < 10; j++) {
			SELFTEST_ASSERT(UART_GetDataSize() == j);
			UART_AppendByteToReceiveRingBuffer(nn);
			SELFTEST_ASSERT(UART_GetDataSize() == j+1);
			nn++;
		}
		nn = next;
		for (int j = 0; j < 10; j++) {
			byte check = UART_GetByte(0);
			SELFTEST_ASSERT(check == nn);
			UART_ConsumeBytes(1);
			nn++;
		}
		SELFTEST_ASSERT(UART_GetDataSize() == 0);
		next = nn;
	}
	for (int i = 0; i < USED_BUFFER_SIZE * 2; i++) {
		UART_AppendByteToReceiveRingBuffer(next);

		int reportedSize = (i+1);
		// detect overflow
		if (reportedSize > (USED_BUFFER_SIZE-1)) {
			reportedSize = (USED_BUFFER_SIZE-1);
		}
		int realSize = UART_GetDataSize();
		// is data size correctly reported?
		SELFTEST_ASSERT(realSize == reportedSize);
		next++;
	}
}

void Test_Commands_Generic() {
	Test_UART();
	Test_Events();

	// reset whole device
	SIM_ClearOBK(0);

	CMD_ExecuteCommand("MqttUser Tester", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTUserName(), "Tester");

	CMD_ExecuteCommand("MqttUser ", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTUserName(), "Tester");

	CMD_ExecuteCommand("MqttPassword Secret1", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTPass(), "Secret1");

	CMD_ExecuteCommand("MqttPassword \"\"", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTPass(), "");

	CMD_ExecuteCommand("MqttPassword \"Xyz\"", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTPass(), "Xyz");

	CMD_ExecuteCommand("MqttUser Tester2", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTUserName(), "Tester2");

	CMD_ExecuteCommand("MqttUser \"\"", 0);
	SELFTEST_ASSERT_STRING(CFG_GetMQTTUserName(), "");

	CMD_ExecuteCommand("SSID1 TPLink123", 0);
	SELFTEST_ASSERT_STRING(CFG_GetWiFiSSID(), "TPLink123");


	// chooses a command from a list by 0-based index
	CMD_ExecuteCommand("SetChannel 10 2",0);
	CMD_ExecuteCommand("Choice $CH10 \"SetChannel 12 222\" \"SetChannel 12 333\" \"SetChannel 12 444\" \"SetChannel 12 555\" \"SetChannel 12 666\"", 0);
	SELFTEST_ASSERT_CHANNEL(12, 444);
	CMD_ExecuteCommand("SetChannel 10 1", 0);
	CMD_ExecuteCommand("Choice $CH10 \"SetChannel 12 222\" \"SetChannel 12 333\" \"SetChannel 12 444\" \"SetChannel 12 555\" \"SetChannel 12 666\"", 0);
	SELFTEST_ASSERT_CHANNEL(12, 333);
	CMD_ExecuteCommand("SetChannel 10 0", 0);
	CMD_ExecuteCommand("Choice $CH10 \"SetChannel 12 222\" \"SetChannel 12 333\" \"SetChannel 12 444\" \"SetChannel 12 555\" \"SetChannel 12 666\"", 0);
	SELFTEST_ASSERT_CHANNEL(12, 222);
	CMD_ExecuteCommand("SetChannel 10 3", 0);
	CMD_ExecuteCommand("Choice $CH10 \"SetChannel 12 222\" \"SetChannel 12 333\" \"SetChannel 12 444\" \"SetChannel 12 555\" \"SetChannel 12 666\"", 0);
	SELFTEST_ASSERT_CHANNEL(12, 555);
	CMD_ExecuteCommand("SetChannel 10 2", 0);
	CMD_ExecuteCommand("Choice $CH10+1 \"SetChannel 12 222\" \"SetChannel 12 333\" \"SetChannel 12 444\" \"SetChannel 12 555\" \"SetChannel 12 666\"", 0);
	SELFTEST_ASSERT_CHANNEL(12, 555);



	CMD_ExecuteCommand("Flags 123455", 0);
	SELFTEST_ASSERT(CFG_GetFlags()== 123455);
	SELFTEST_ASSERT(CFG_GetFlags64() == 123455);
	CMD_ExecuteCommand("Flags 444", 0);
	SELFTEST_ASSERT(CFG_GetFlags() == 444);
	SELFTEST_ASSERT(CFG_GetFlags64() == 444);
	//CMD_ExecuteCommand("Flags 8589934592", 0);
	//SELFTEST_ASSERT(CFG_GetFlags64() == 8589934592);


	// https://github.com/openshwprojects/OpenBK7231T_App/issues/1646
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x0 setChannel 12 1", 0);
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x1 setChannel 12 2", 0);
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x10 setChannel 12 3", 0);
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x4 setChannel 12 4", 0);
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x5 setChannel 12 5", 0);
	CMD_ExecuteCommand("addEventHandler2 IR_NEC 0xEF00 0x6 setChannel 12 6", 0);

	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x0);
	SELFTEST_ASSERT_CHANNEL(12, 1);
	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x1);
	SELFTEST_ASSERT_CHANNEL(12, 2);
	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x10);
	SELFTEST_ASSERT_CHANNEL(12, 3);
	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x4);
	SELFTEST_ASSERT_CHANNEL(12, 4);
	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x5);
	SELFTEST_ASSERT_CHANNEL(12, 5);
	EventHandlers_FireEvent2(CMD_EVENT_IR_NEC, 0xEF00, 0x6);
	SELFTEST_ASSERT_CHANNEL(12, 6);

	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x0, 0);
	SELFTEST_ASSERT_CHANNEL(12, 1);
	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x1, 0);
	SELFTEST_ASSERT_CHANNEL(12, 2);
	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x10, 0);
	SELFTEST_ASSERT_CHANNEL(12, 3);
	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x4, 0);
	SELFTEST_ASSERT_CHANNEL(12, 4);
	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x5, 0);
	SELFTEST_ASSERT_CHANNEL(12, 5);
	EventHandlers_FireEvent3(CMD_EVENT_IR_NEC, 0xEF00, 0x6, 0);
	SELFTEST_ASSERT_CHANNEL(12, 6);
}


#endif

;/* ASM Define for CH376      */
;/* Website:  http://wch.cn   */
;/* Email:    tech@wch.cn     */
;/* Author:   W.ch 2008.10    */
;/* V1.0 for CH376            */

;/********************************************************************************************************************** */
;/*�������ͺͳ������� */


;#ifndef		TRUE
TRUE				EQU		1
FALSE				EQU		0
;#endif
;#ifndef		NULL
NULL				EQU		0
;#endif

;/********************************************************************************************************************** */
;/*Ӳ������ */

CH376_DAT_BLOCK_LEN	EQU		040H			;/*USB�������ݰ�, ���ݿ����󳤶�, Ĭ�ϻ������ĳ��� */

;/********************************************************************************************************************** */
;/*������� */
;/*�����������CH375оƬ, �����������ݻ���������ݵĿ��ֲܾ���ͬ) */
;/*һ���������˳�����:
;          һ��������(���ڴ��ڷ�ʽ,������֮ǰ����Ҫ����ͬ����),
;          ���ɸ���������(������0��),
;          �����ж�֪ͨ ���� ���ɸ��������(������0��), ��ѡһ, ���ж�֪ͨ��һ��û���������, �����������һ���������ж�
;       ��CMD01_WR_REQ_DATA��������, ˳�����: һ��������, һ���������, ���ɸ���������
;   ��������������: CMDxy_NAME
;       ���е�x��y��������, x˵�������������ݸ���(�ֽ���), y˵������������ݸ���(�ֽ���), y�����H��˵�������ж�֪ͨ,
;       ��Щ�����ܹ�ʵ��0������ֽڵ����ݿ��д, ���ݿ鱾�����ֽ���δ����������x��y֮�� */
;/*���ļ�Ĭ�ϻ�ͬʱ�ṩ��CH375оƬ��������ݵ��������ʽ����ȥ��x��y֮��), �������Ҫ, ��ô���Զ���_NO_CH375_COMPATIBLE_��ֹ */

;/********************************************************************************************************************** */
;/*��Ҫ����(�ֲ�һ), ���� */

CMD01_GET_IC_VER	EQU		001H			;/*��ȡоƬ���̼��汾 */
;/*���: �汾��( λ7Ϊ0, λ6Ϊ1, λ5~λ0Ϊ�汾�� ) */
;/*          CH376���ذ汾�ŵ�ֵΪ041H���汾��Ϊ01H */

CMD21_SET_BAUDRATE	EQU		002H			;/*���ڷ�ʽ: ���ô���ͨѶ������(�ϵ���߸�λ���Ĭ�ϲ�����Ϊ9600bps,��D4/D5/D6����ѡ��) */
;/*����: �����ʷ�Ƶϵ��, �����ʷ�Ƶ���� */
;/*���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) */

CMD00_ENTER_SLEEP	EQU		003H			;/*����˯��״̬ */

CMD00_RESET_ALL		EQU		005H			;/*ִ��Ӳ����λ */

CMD11_CHECK_EXIST	EQU		006H			;/*����ͨѶ�ӿں͹���״̬ */
;/*����: �������� */
;/*���: �������ݵİ�λȡ�� */

CMD20_CHK_SUSPEND	EQU		00BH			;/*�豸��ʽ: ���ü��USB���߹���״̬�ķ�ʽ */
;/*����: ����10H, ��鷽ʽ */
;/*          00H=�����USB����, 04H=��50mSΪ������USB����, 05H=��10mSΪ������USB���� */

CMD20_SET_SDO_INT	EQU		00BH			;/*SPI�ӿڷ�ʽ: ����SPI��SDO���ŵ��жϷ�ʽ */
;/*����: ����16H, �жϷ�ʽ */
;/*          10H=��ֹSDO���������ж����,��SCSƬѡ��Чʱ��̬�����ֹ, 90H=SDO������SCSƬѡ��Чʱ�����ж�������� */

CMD14_GET_FILE_SIZE	EQU		00CH			;/*�����ļ�ģʽ: ��ȡ��ǰ�ļ����� */
;/*����: ����68H */
;/*���: ��ǰ�ļ�����(�ܳ���32λ,���ֽ���ǰ) */

CMD50_SET_FILE_SIZE	EQU		00DH			;/*�����ļ�ģʽ: ���õ�ǰ�ļ����� */
;/*����: ����68H, ��ǰ�ļ�����(�ܳ���32λ,���ֽ���ǰ) */

CMD11_SET_USB_MODE	EQU		015H			;/*����USB����ģʽ */
;/*����: ģʽ���� */
;/*      00H=δ���õ��豸��ʽ, 01H=�����õ��豸��ʽ����ʹ���ⲿ�̼�ģʽ(���ڲ�֧��), 02H=�����õ��豸��ʽ����ʹ�����ù̼�ģʽ */
;/*      03H=SD������ģʽ/δ���õ�����ģʽ,���ڹ����ʹ�ȡSD���е��ļ� */
;/*      04H=δ���õ�������ʽ, 05H=�����õ�������ʽ, 06H=�����õ�������ʽ�����Զ�����SOF��, 07H=�����õ�������ʽ���Ҹ�λUSB���� */
;/*���: ����״̬( CMD_RET_SUCCESS��CMD_RET_ABORT, ����ֵ˵������δ��� ) */

CMD01_GET_STATUS	EQU		022H			;/*��ȡ�ж�״̬��ȡ���ж����� */
;/*���: �ж�״̬ */

CMD00_UNLOCK_USB	EQU		023H			;/*�豸��ʽ: �ͷŵ�ǰUSB������ */

CMD01_RD_USB_DATA0	EQU		027H			;/*�ӵ�ǰUSB�жϵĶ˵㻺�������������˵�Ľ��ջ�������ȡ���ݿ� */
;/*���: ����, ������ */

CMD01_RD_USB_DATA	EQU		028H			;/*�豸��ʽ: �ӵ�ǰUSB�жϵĶ˵㻺������ȡ���ݿ�, ���ͷŻ�����, �൱�� CMD01_RD_USB_DATA0 + CMD00_UNLOCK_USB */
;/*���: ����, ������ */

CMD10_WR_USB_DATA7	EQU		02BH			;/*�豸��ʽ: ��USB�˵�2�ķ��ͻ�����д�����ݿ� */
;/*����: ����, ������ */

CMD10_WR_HOST_DATA	EQU		02CH			;/*��USB�����˵�ķ��ͻ�����д�����ݿ� */
;/*����: ����, ������ */

CMD01_WR_REQ_DATA	EQU		02DH			;/*���ڲ�ָ��������д����������ݿ� */
;/*���: ���� */
;/*����: ������ */

CMD20_WR_OFS_DATA	EQU		02EH			;/*���ڲ�������ָ��ƫ�Ƶ�ַд�����ݿ� */
;/*����: ƫ��, ����, ������ */

CMD10_SET_FILE_NAME	EQU		02FH			;/*�����ļ�ģʽ: ���ý�Ҫ�������ļ����ļ��� */
;/*����: ��0�������ַ���(��������0���ڳ��Ȳ�����14���ַ�) */

;/********************************************************************************************************************** */
;/*��Ҫ����(�ֲ�һ), ����, �������������ڲ�������ʱ�����ж�֪ͨ, ��������û��������� */

CMD0H_DISK_CONNECT	EQU		030H			;/*�����ļ�ģʽ/��֧��SD��: �������Ƿ����� */
;/*����ж� */

CMD0H_DISK_MOUNT	EQU		031H			;/*�����ļ�ģʽ: ��ʼ�����̲����Դ����Ƿ���� */
;/*����ж� */

CMD0H_FILE_OPEN		EQU		032H			;/*�����ļ�ģʽ: ���ļ�����Ŀ¼(�ļ���),����ö���ļ���Ŀ¼(�ļ���) */
;/*����ж� */

CMD0H_FILE_ENUM_GO	EQU		033H			;/*�����ļ�ģʽ: ����ö���ļ���Ŀ¼(�ļ���) */
;/*����ж� */

CMD0H_FILE_CREATE	EQU		034H			;/*�����ļ�ģʽ: �½��ļ�,����ļ��Ѿ�������ô��ɾ�� */
;/*����ж� */

CMD0H_FILE_ERASE	EQU		035H			;/*�����ļ�ģʽ: ɾ���ļ�,����Ѿ�����ֱ��ɾ��,��������ļ����ȴ���ɾ��,��Ŀ¼�����ȴ� */
;/*����ж� */

CMD1H_FILE_CLOSE	EQU		036H			;/*�����ļ�ģʽ: �رյ�ǰ�Ѿ��򿪵��ļ�����Ŀ¼(�ļ���) */
;/*����: �Ƿ����������ļ����� */
;/*         00H=��ֹ���³���, 01H=�������³��� */
;/*����ж� */

CMD1H_DIR_INFO_READ	EQU		037H			;/*�����ļ�ģʽ: ��ȡ�ļ���Ŀ¼��Ϣ */
;/*����: ָ����Ҫ��ȡ��Ŀ¼��Ϣ�ṹ�������ڵ������� */
;/*          �����ŷ�ΧΪ00H~0FH, ������0FFH��Ϊ��ǰ�Ѿ��򿪵��ļ� */
;/*����ж� */

CMD0H_DIR_INFO_SAVE	EQU		038H			;/*�����ļ�ģʽ: �����ļ���Ŀ¼��Ϣ */
;/*����ж� */

CMD4H_BYTE_LOCATE	EQU		039H			;/*�����ļ�ģʽ: ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
;/*����: ƫ���ֽ���(�ܳ���32λ,���ֽ���ǰ) */
;/*����ж� */

CMD2H_BYTE_READ		EQU		03AH			;/*�����ļ�ģʽ: ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
;/*����: �����ȡ���ֽ���(�ܳ���16λ,���ֽ���ǰ) */
;/*����ж� */

CMD0H_BYTE_RD_GO	EQU		03BH			;/*�����ļ�ģʽ: �����ֽڶ� */
;/*����ж� */

CMD2H_BYTE_WRITE	EQU		03CH			;/*�����ļ�ģʽ: ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
;/*����: ����д����ֽ���(�ܳ���16λ,���ֽ���ǰ) */
;/*����ж� */

CMD0H_BYTE_WR_GO	EQU		03DH			;/*�����ļ�ģʽ: �����ֽ�д */
;/*����ж� */

CMD0H_DISK_CAPACITY	EQU		03EH			;/*�����ļ�ģʽ: ��ѯ������������ */
;/*����ж� */

CMD0H_DISK_QUERY	EQU		03FH			;/*�����ļ�ģʽ: ��ѯ���̿ռ���Ϣ */
;/*����ж� */

CMD0H_DIR_CREATE	EQU		040H			;/*�����ļ�ģʽ: �½�Ŀ¼(�ļ���)����,���Ŀ¼�Ѿ�������ôֱ�Ӵ� */
;/*����ж� */

CMD4H_SEC_LOCATE	EQU		04AH			;/*�����ļ�ģʽ: ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
;/*����: ƫ��������(�ܳ���32λ,���ֽ���ǰ) */
;/*����ж� */

CMD1H_SEC_READ		EQU		04BH			;/*�����ļ�ģʽ/��֧��SD��: ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
;/*����: �����ȡ�������� */
;/*����ж� */

CMD1H_SEC_WRITE		EQU		04CH			;/*�����ļ�ģʽ/��֧��SD��: ������Ϊ��λ�ڵ�ǰλ��д�����ݿ� */
;/*����: ����д��������� */
;/*����ж� */

CMD0H_DISK_BOC_CMD	EQU		050H			;/*������ʽ/��֧��SD��: ��USB�洢��ִ��BulkOnly����Э������� */
;/*����ж� */

CMD5H_DISK_READ		EQU		054H			;/*������ʽ/��֧��SD��: ��USB�洢������������ */
;/*����: LBA����������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
;/*����ж� */

CMD0H_DISK_RD_GO	EQU		055H			;/*������ʽ/��֧��SD��: ����ִ��USB�洢������������������ */
;/*����ж� */

CMD5H_DISK_WRITE	EQU		056H			;/*������ʽ/��֧��SD��: ��USB�洢��д�������� */
;/*����: LBA����������ַ(�ܳ���32λ, ���ֽ���ǰ), ������(01H~FFH) */
;/*����ж� */

CMD0H_DISK_WR_GO	EQU		057H			;/*������ʽ/��֧��SD��: ����ִ��USB�洢������������д���� */
;/*����ж� */

;/********************************************************************************************************************** */
;/*��������(�ֲ��), ��̫���û�����Ϊ����CH375��CH372���� */

CMD10_SET_USB_SPEED	EQU		004H			;/*����USB�����ٶ�, ��ÿ��CMD11_SET_USB_MODE����USB����ģʽʱ���Զ��ָ���12Mbpsȫ�� */
;/*����: �����ٶȴ��� */
;/*          00H=12Mbpsȫ��FullSpeed��Ĭ��ֵ��, 01H=1.5Mbps�����޸�Ƶ�ʣ�, 02H=1.5Mbps����LowSpeed */

CMD11_GET_DEV_RATE	EQU		00AH			;/*������ʽ: ��ȡ��ǰ���ӵ�USB�豸�������������� */
;/*����: ����07H */
;/*���: ������������ */
;/*          λ4Ϊ1����1.5Mbps����USB�豸, ������12Mbpsȫ��USB�豸 */

CMD11_GET_TOGGLE	EQU		00AH			;/*��ȡOUT�����ͬ��״̬ */
;/*����: ����1AH */
;/*���: ͬ��״̬ */
;/*          λ4Ϊ1��OUT����ͬ��, ����OUT����ͬ�� */

CMD11_READ_VAR8		EQU		00AH			;/*��ȡָ����8λ�ļ�ϵͳ���� */
;/*����: ������ַ */
;/*���: ���� */

;/*CMD11_GET_MAX_LUN	= CMD11_READ_VAR8( VAR_UDISK_LUN )*/	;/*������ʽ: ��ȡUSB�洢�����͵�ǰ�߼���Ԫ�� */

CMD20_SET_RETRY		EQU		00BH			;/*������ʽ: ����USB������������Դ��� */
;/*����: ����25H, ���Դ��� */
;/*          λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������, λ7Ϊ1λ6Ϊ1���յ�NAKʱ�������3��, λ5~λ0Ϊ��ʱ������Դ��� */

CMD20_WRITE_VAR8	EQU		00BH			;/*����ָ����8λ�ļ�ϵͳ���� */
;/*����: ������ַ, ���� */

;/*CMD20_SET_DISK_LUN	= CMD20_WRITE_VAR8( VAR_UDISK_LUN )*/	;/*������ʽ: ����USB�洢���ĵ�ǰ�߼���Ԫ�� */

CMD14_READ_VAR32	EQU		00CH			;/*��ȡָ����32λ�ļ�ϵͳ���� */
;/*����: ������ַ */
;/*���: ����(�ܳ���32λ,���ֽ���ǰ) */

CMD50_WRITE_VAR32	EQU		00DH			;/*����ָ����32λ�ļ�ϵͳ���� */
;/*����: ������ַ, ����(�ܳ���32λ,���ֽ���ǰ) */

CMD01_DELAY_100US	EQU		00FH			;/*��ʱ100uS(���ڲ�֧��) */
;/*���: ��ʱ�ڼ����0,��ʱ���������0 */

CMD40_SET_USB_ID	EQU		012H			;/*�豸��ʽ: ����USB����VID�Ͳ�ƷPID */
;/*����: ����ID���ֽ�, ����ID���ֽ�, ��ƷID���ֽ�, ��ƷID���ֽ� */

CMD10_SET_USB_ADDR	EQU		013H			;/*����USB��ַ */
;/*����: ��ֵַ */

CMD01_TEST_CONNECT	EQU		016H			;/*������ʽ/��֧��SD��: ���USB�豸����״̬ */
;/*���: ״̬( USB_INT_CONNECT��USB_INT_DISCONNECT��USB_INT_USB_READY, ����ֵ˵������δ��� ) */

CMD00_ABORT_NAK		EQU		017H			;/*������ʽ: ������ǰNAK������ */

CMD10_SET_ENDP2		EQU		018H			;/*�豸��ʽ(���ڲ�֧��): ����USB�˵�0�Ľ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

CMD10_SET_ENDP3		EQU		019H			;/*�豸��ʽ(���ڲ�֧��): ����USB�˵�0�ķ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

CMD10_SET_ENDP4		EQU		01AH			;/*�豸��ʽ(���ڲ�֧��): ����USB�˵�1�Ľ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1110-��æNAK, 1111-����STALL */

CMD10_SET_ENDP5		EQU		01BH			;/*�豸��ʽ(���ڲ�֧��): ����USB�˵�1�ķ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000~1000-����ACK, 1110-��æNAK, 1111-����STALL */

CMD10_SET_ENDP6		EQU		01CH			;/*����USB�˵�2/�����˵�Ľ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-������������ACK, 1110-��æNAK, 1111-����STALL */

CMD10_SET_ENDP7		EQU		01DH			;/*����USB�˵�2/�����˵�ķ����� */
;/*����: ������ʽ */
;/*          λ7Ϊ1��λ6Ϊͬ������λ, ����ͬ������λ���� */
;/*          λ3~λ0Ϊ������Ӧ��ʽ:  0000-����ACK, 1101-����������Ӧ��, 1110-��æNAK, 1111-����STALL */

CMD00_DIRTY_BUFFER	EQU		025H			;/*�����ļ�ģʽ: ����ڲ��Ĵ��̺��ļ������� */

CMD10_WR_USB_DATA3	EQU		029H			;/*�豸��ʽ(���ڲ�֧��): ��USB�˵�0�ķ��ͻ�����д�����ݿ� */
;/*����: ����, ������ */

CMD10_WR_USB_DATA5	EQU		02AH			;/*�豸��ʽ(���ڲ�֧��): ��USB�˵�1�ķ��ͻ�����д�����ݿ� */
;/*����: ����, ������ */

;/********************************************************************************************************************** */
;/*��������(�ֲ��), ��̫���û�����Ϊ����CH375��CH372����, �������������ڲ�������ʱ�����ж�֪ͨ, ��������û��������� */

CMD1H_CLR_STALL		EQU		041H			;/*������ʽ: ���ƴ���-����˵���� */
;/*����: �˵�� */
;/*����ж� */

CMD1H_SET_ADDRESS	EQU		045H			;/*������ʽ: ���ƴ���-����USB��ַ */
;/*����: ��ֵַ */
;/*����ж� */

CMD1H_GET_DESCR		EQU		046H			;/*������ʽ: ���ƴ���-��ȡ������ */
;/*����: ���������� */
;/*����ж� */

CMD1H_SET_CONFIG	EQU		049H			;/*������ʽ: ���ƴ���-����USB���� */
;/*����: ����ֵ */
;/*����ж� */

CMD0H_AUTO_SETUP	EQU		04DH			;/*������ʽ/��֧��SD��: �Զ�����USB�豸 */
;/*����ж� */

CMD2H_ISSUE_TKN_X	EQU		04EH			;/*������ʽ: ����ͬ������, ִ������, ������ɴ��� CMD10_SET_ENDP6/CMD10_SET_ENDP7 + CMD1H_ISSUE_TOKEN */
;/*����: ͬ����־, �������� */
;/*          ͬ����־��λ7Ϊ�����˵�IN��ͬ������λ, λ6Ϊ�����˵�OUT��ͬ������λ, λ5~λ0����Ϊ0 */
;/*          �������Եĵ�4λ������, ��4λ�Ƕ˵�� */
;/*����ж� */

CMD1H_ISSUE_TOKEN	EQU		04FH			;/*������ʽ: ��������, ִ������, ������CMD2H_ISSUE_TKN_X���� */
;/*����: �������� */
;/*          ��4λ������, ��4λ�Ƕ˵�� */
;/*����ж� */

CMD0H_DISK_INIT		EQU		051H			;/*������ʽ/��֧��SD��: ��ʼ��USB�洢�� */
;/*����ж� */

CMD0H_DISK_RESET	EQU		052H			;/*������ʽ/��֧��SD��: ���ƴ���-��λUSB�洢�� */
;/*����ж� */

CMD0H_DISK_SIZE		EQU		053H			;/*������ʽ/��֧��SD��: ��ȡUSB�洢�������� */
;/*����ж� */

CMD0H_DISK_INQUIRY	EQU		058H			;/*������ʽ/��֧��SD��: ��ѯUSB�洢������ */
;/*����ж� */

CMD0H_DISK_READY	EQU		059H			;/*������ʽ/��֧��SD��: ���USB�洢������ */
;/*����ж� */

CMD0H_DISK_R_SENSE	EQU		05AH			;/*������ʽ/��֧��SD��: ���USB�洢������ */
;/*����ж� */

CMD0H_RD_DISK_SEC	EQU		05BH			;/*�����ļ�ģʽ: �Ӵ��̶�ȡһ�����������ݵ��ڲ������� */
;/*����ж� */

CMD0H_WR_DISK_SEC	EQU		05CH			;/*�����ļ�ģʽ: ���ڲ���������һ������������д����� */
;/*����ж� */

CMD0H_DISK_MAX_LUN	EQU		05DH			;/*������ʽ: ���ƴ���-��ȡUSB�洢������߼���Ԫ�� */
;/*����ж� */

;/********************************************************************************************************************** */
;/*���¶���ֻ��Ϊ�˼���CH375��INCLUDE�ļ��е��������Ƹ�ʽ */

;#ifndef	_NO_CH375_COMPATIBLE_
CMD_GET_IC_VER		EQU		CMD01_GET_IC_VER
CMD_SET_BAUDRATE	EQU		CMD21_SET_BAUDRATE
CMD_ENTER_SLEEP		EQU		CMD00_ENTER_SLEEP
CMD_RESET_ALL		EQU		CMD00_RESET_ALL
CMD_CHECK_EXIST		EQU		CMD11_CHECK_EXIST
CMD_CHK_SUSPEND		EQU		CMD20_CHK_SUSPEND
CMD_SET_SDO_INT		EQU		CMD20_SET_SDO_INT
CMD_GET_FILE_SIZE	EQU		CMD14_GET_FILE_SIZE
CMD_SET_FILE_SIZE	EQU		CMD50_SET_FILE_SIZE
CMD_SET_USB_MODE	EQU		CMD11_SET_USB_MODE
CMD_GET_STATUS		EQU		CMD01_GET_STATUS
CMD_UNLOCK_USB		EQU		CMD00_UNLOCK_USB
CMD_RD_USB_DATA0	EQU		CMD01_RD_USB_DATA0
CMD_RD_USB_DATA		EQU		CMD01_RD_USB_DATA
CMD_WR_USB_DATA7	EQU		CMD10_WR_USB_DATA7
CMD_WR_HOST_DATA	EQU		CMD10_WR_HOST_DATA
CMD_WR_REQ_DATA		EQU		CMD01_WR_REQ_DATA
CMD_WR_OFS_DATA		EQU		CMD20_WR_OFS_DATA
CMD_SET_FILE_NAME	EQU		CMD10_SET_FILE_NAME
CMD_DISK_CONNECT	EQU		CMD0H_DISK_CONNECT
CMD_DISK_MOUNT		EQU		CMD0H_DISK_MOUNT
CMD_FILE_OPEN		EQU		CMD0H_FILE_OPEN
CMD_FILE_ENUM_GO	EQU		CMD0H_FILE_ENUM_GO
CMD_FILE_CREATE		EQU		CMD0H_FILE_CREATE
CMD_FILE_ERASE		EQU		CMD0H_FILE_ERASE
CMD_FILE_CLOSE		EQU		CMD1H_FILE_CLOSE
CMD_DIR_INFO_READ	EQU		CMD1H_DIR_INFO_READ
CMD_DIR_INFO_SAVE	EQU		CMD0H_DIR_INFO_SAVE
CMD_BYTE_LOCATE		EQU		CMD4H_BYTE_LOCATE
CMD_BYTE_READ		EQU		CMD2H_BYTE_READ
CMD_BYTE_RD_GO		EQU		CMD0H_BYTE_RD_GO
CMD_BYTE_WRITE		EQU		CMD2H_BYTE_WRITE
CMD_BYTE_WR_GO		EQU		CMD0H_BYTE_WR_GO
CMD_DISK_CAPACITY	EQU		CMD0H_DISK_CAPACITY
CMD_DISK_QUERY		EQU		CMD0H_DISK_QUERY
CMD_DIR_CREATE		EQU		CMD0H_DIR_CREATE
CMD_SEC_LOCATE		EQU		CMD4H_SEC_LOCATE
CMD_SEC_READ		EQU		CMD1H_SEC_READ
CMD_SEC_WRITE		EQU		CMD1H_SEC_WRITE
CMD_DISK_BOC_CMD	EQU		CMD0H_DISK_BOC_CMD
CMD_DISK_READ		EQU		CMD5H_DISK_READ
CMD_DISK_RD_GO		EQU		CMD0H_DISK_RD_GO
CMD_DISK_WRITE		EQU		CMD5H_DISK_WRITE
CMD_DISK_WR_GO		EQU		CMD0H_DISK_WR_GO
CMD_SET_USB_SPEED	EQU		CMD10_SET_USB_SPEED
CMD_GET_DEV_RATE	EQU		CMD11_GET_DEV_RATE
CMD_GET_TOGGLE		EQU		CMD11_GET_TOGGLE
CMD_READ_VAR8		EQU		CMD11_READ_VAR8
CMD_SET_RETRY		EQU		CMD20_SET_RETRY
CMD_WRITE_VAR8		EQU		CMD20_WRITE_VAR8
CMD_READ_VAR32		EQU		CMD14_READ_VAR32
CMD_WRITE_VAR32		EQU		CMD50_WRITE_VAR32
CMD_DELAY_100US		EQU		CMD01_DELAY_100US
CMD_SET_USB_ID		EQU		CMD40_SET_USB_ID
CMD_SET_USB_ADDR	EQU		CMD10_SET_USB_ADDR
CMD_TEST_CONNECT	EQU		CMD01_TEST_CONNECT
CMD_ABORT_NAK		EQU		CMD00_ABORT_NAK
CMD_SET_ENDP2		EQU		CMD10_SET_ENDP2
CMD_SET_ENDP3		EQU		CMD10_SET_ENDP3
CMD_SET_ENDP4		EQU		CMD10_SET_ENDP4
CMD_SET_ENDP5		EQU		CMD10_SET_ENDP5
CMD_SET_ENDP6		EQU		CMD10_SET_ENDP6
CMD_SET_ENDP7		EQU		CMD10_SET_ENDP7
CMD_DIRTY_BUFFER	EQU		CMD00_DIRTY_BUFFER
CMD_WR_USB_DATA3	EQU		CMD10_WR_USB_DATA3
CMD_WR_USB_DATA5	EQU		CMD10_WR_USB_DATA5
CMD_CLR_STALL		EQU		CMD1H_CLR_STALL
CMD_SET_ADDRESS		EQU		CMD1H_SET_ADDRESS
CMD_GET_DESCR		EQU		CMD1H_GET_DESCR
CMD_SET_CONFIG		EQU		CMD1H_SET_CONFIG
CMD_AUTO_SETUP		EQU		CMD0H_AUTO_SETUP
CMD_ISSUE_TKN_X		EQU		CMD2H_ISSUE_TKN_X
CMD_ISSUE_TOKEN		EQU		CMD1H_ISSUE_TOKEN
CMD_DISK_INIT		EQU		CMD0H_DISK_INIT
CMD_DISK_RESET		EQU		CMD0H_DISK_RESET
CMD_DISK_SIZE		EQU		CMD0H_DISK_SIZE
CMD_DISK_INQUIRY	EQU		CMD0H_DISK_INQUIRY
CMD_DISK_READY		EQU		CMD0H_DISK_READY
CMD_DISK_R_SENSE	EQU		CMD0H_DISK_R_SENSE
CMD_RD_DISK_SEC		EQU		CMD0H_RD_DISK_SEC
CMD_WR_DISK_SEC		EQU		CMD0H_WR_DISK_SEC
CMD_DISK_MAX_LUN	EQU		CMD0H_DISK_MAX_LUN
;#endif

;/********************************************************************************************************************** */
;/*���ڷ�ʽ, ״̬�˿�(������˿�)��λ���� */
;#ifndef	PARA_STATE_INTB
PARA_STATE_INTB		EQU		080H			;/*���ڷ�ʽ״̬�˿ڵ�λ7: �жϱ�־,����Ч */
PARA_STATE_BUSY		EQU		010H			;/*���ڷ�ʽ״̬�˿ڵ�λ4: æ��־,����Ч */
;#endif

;/********************************************************************************************************************** */
;/*���ڷ�ʽ, ��������ǰ������ͬ���� */
;#ifndef	SER_CMD_TIMEOUT
SER_CMD_TIMEOUT		EQU		020H			;/*�������ʱʱ��, ��λΪmS, ͬ����֮�估ͬ������������֮��ļ��Ӧ�þ�����, ��ʱ��Ĵ�����ʽΪ���� */
SER_SYNC_CODE1		EQU		057H			;/*���������ĵ�1������ͬ���� */
SER_SYNC_CODE2		EQU		0ABH			;/*���������ĵ�2������ͬ���� */
;#endif

;/********************************************************************************************************************** */
;/*����״̬ */

;#ifndef	CMD_RET_SUCCESS
CMD_RET_SUCCESS		EQU		051H			;/*��������ɹ� */
CMD_RET_ABORT		EQU		05FH			;/*�������ʧ�� */
;#endif

;/********************************************************************************************************************** */
;/*USB�ж�״̬ */

;#ifndef	USB_INT_EP0_SETUP

;/*����״̬����Ϊ�����¼��ж�, ���ͨ��CMD20_CHK_SUSPEND����USB���߹�����, ��ô���봦��USB���߹����˯�߻��ѵ��ж�״̬ */
USB_INT_USB_SUSPEND	EQU		005H			;/*USB���߹����¼� */
USB_INT_WAKE_UP		EQU		006H			;/*��˯���б������¼� */

;/*����״̬����0XH����USB�豸��ʽ */
;/*  ���ù̼�ģʽ��ֻ��Ҫ����: USB_INT_EP1_OUT, USB_INT_EP1_IN, USB_INT_EP2_OUT, USB_INT_EP2_IN */
;/*  λ7-λ4Ϊ0000 */
;/*  λ3-λ2ָʾ��ǰ����, 00=OUT, 10=IN, 11=SETUP */
;/*  λ1-λ0ָʾ��ǰ�˵�, 00=�˵�0, 01=�˵�1, 10=�˵�2, 11=USB���߸�λ */
USB_INT_EP0_SETUP	EQU		00CH			;/*USB�˵�0��SETUP */
USB_INT_EP0_OUT		EQU		000H			;/*USB�˵�0��OUT */
USB_INT_EP0_IN		EQU		008H			;/*USB�˵�0��IN */
USB_INT_EP1_OUT		EQU		001H			;/*USB�˵�1��OUT */
USB_INT_EP1_IN		EQU		009H			;/*USB�˵�1��IN */
USB_INT_EP2_OUT		EQU		002H			;/*USB�˵�2��OUT */
USB_INT_EP2_IN		EQU		00AH			;/*USB�˵�2��IN */
;/*USB_INT_BUS_RESET	EQU		00000XX11B */		;/*USB���߸�λ */
USB_INT_BUS_RESET1	EQU		003H			;/*USB���߸�λ */
USB_INT_BUS_RESET2	EQU		007H			;/*USB���߸�λ */
USB_INT_BUS_RESET3	EQU		00BH			;/*USB���߸�λ */
USB_INT_BUS_RESET4	EQU		00FH			;/*USB���߸�λ */

;#endif

;/*����״̬����2XH-3XH����USB������ʽ��ͨѶʧ�ܴ��� */
;/*  λ7-λ6Ϊ00 */
;/*  λ5Ϊ1 */
;/*  λ4ָʾ��ǰ���յ����ݰ��Ƿ�ͬ�� */
;/*  λ3-λ0ָʾ����ͨѶʧ��ʱUSB�豸��Ӧ��: 0010=ACK, 1010=NAK, 1110=STALL, 0011=DATA0, 1011=DATA1, XX00=��ʱ */
;/*USB_INT_RET_ACK	EQU		0001X0010B */H			;/*����:����IN���񷵻�ACK */
;/*USB_INT_RET_NAK	EQU		0001X1010B */H			;/*����:����NAK */
;/*USB_INT_RET_STALL	EQU		0001X1110B */		;/*����:����STALL */
;/*USB_INT_RET_DATA0	EQU		0001X0011B */		;/*����:����OUT/SETUP���񷵻�DATA0 */
;/*USB_INT_RET_DATA1	EQU		0001X1011B */		;/*����:����OUT/SETUP���񷵻�DATA1 */
;/*USB_INT_RET_TOUT	EQU		0001XXX00B */H			;/*����:���س�ʱ */
;/*USB_INT_RET_TOGX	EQU		00010X011B */H			;/*����:����IN���񷵻����ݲ�ͬ�� */
;/*USB_INT_RET_PID	EQU		0001XXXXXB */H			;/*����:δ���� */

;/*����״̬����1XH����USB������ʽ�Ĳ���״̬���� */
;#ifndef	USB_INT_SUCCESS
USB_INT_SUCCESS		EQU		014H			;/*USB������ߴ�������ɹ� */
USB_INT_CONNECT		EQU		015H			;/*��⵽USB�豸�����¼�, �����������ӻ��߶Ͽ����������� */
USB_INT_DISCONNECT	EQU		016H			;/*��⵽USB�豸�Ͽ��¼� */
USB_INT_BUF_OVER	EQU		017H			;/*USB��������������������̫�໺������� */
USB_INT_USB_READY	EQU		018H			;/*USB�豸�Ѿ�����ʼ��(�Ѿ�����USB��ַ) */
USB_INT_DISK_READ	EQU		01DH			;/*USB�洢���������ݶ��� */
USB_INT_DISK_WRITE	EQU		01EH			;/*USB�洢����������д�� */
USB_INT_DISK_ERR	EQU		01FH			;/*USB�洢������ʧ�� */
;#endif

;/*����״̬�������������ļ�ģʽ�µ��ļ�ϵͳ������ */
;#ifndef	ERR_DISK_DISCON
ERR_DISK_DISCON		EQU		082H			;/*������δ����,���ܴ����Ѿ��Ͽ� */
ERR_LARGE_SECTOR	EQU		084H			;/*���̵�����̫��,ֻ֧��ÿ����512�ֽ� */
ERR_TYPE_ERROR		EQU		092H			;/*���̷������Ͳ�֧��,ֻ֧��FAT12/FAT16/BigDOS/FAT32,��Ҫ�ɴ��̹����������·��� */
ERR_BPB_ERROR		EQU		0A1H			;/*������δ��ʽ��,���߲�������,��Ҫ��WINDOWS����Ĭ�ϲ������¸�ʽ�� */
ERR_DISK_FULL		EQU		0B1H			;/*�����ļ�̫��,ʣ��ռ�̫�ٻ����Ѿ�û��,��Ҫ�������� */
ERR_FDT_OVER		EQU		0B2H			;/*Ŀ¼(�ļ���)���ļ�̫��,û�п��е�Ŀ¼��,FAT12/FAT16��Ŀ¼�µ��ļ���Ӧ������512��,��Ҫ�������� */
ERR_FILE_CLOSE		EQU		0B4H			;/*�ļ��Ѿ��ر�,�����Ҫʹ��,Ӧ�����´��ļ� */
ERR_OPEN_DIR		EQU		041H			;/*ָ��·����Ŀ¼(�ļ���)���� */
ERR_MISS_FILE		EQU		042H			;/*ָ��·�����ļ�û���ҵ�,�������ļ����ƴ��� */
ERR_FOUND_NAME		EQU		043H			;/*��������ƥ����ļ���,������Ҫ���Ŀ¼(�ļ���)��ʵ�ʽ��ȴ�����ļ� */
;/* �����ļ�ϵͳ�����������ļ�ϵͳ�ӳ��� */
ERR_MISS_DIR		EQU		0B3H			;/*ָ��·����ĳ����Ŀ¼(�ļ���)û���ҵ�,������Ŀ¼���ƴ��� */
ERR_LONG_BUF_OVER	EQU		048H			;/*���ļ���������� */
ERR_LONG_NAME_ERR	EQU		049H			;/*���ļ���û�ж�Ӧ�ĳ��ļ������߳��ļ������� */
ERR_NAME_EXIST		EQU		04AH			;/*ͬ���Ķ��ļ��Ѿ�����,����������������һ�����ļ��� */
;#endif

;/********************************************************************************************************************** */
;/*����״̬�������������ļ�ģʽ�µĴ��̼��ļ�״̬, VAR_DISK_STATUS */
;#ifndef	DEF_DISK_UNKNOWN
DEF_DISK_UNKNOWN	EQU		000H			;/*��δ��ʼ��,δ֪״̬ */
DEF_DISK_DISCONN	EQU		001H			;/*����û�����ӻ����Ѿ��Ͽ� */
DEF_DISK_CONNECT	EQU		002H			;/*�����Ѿ�����,������δ��ʼ�������޷�ʶ��ô��� */
DEF_DISK_MOUNTED	EQU		003H			;/*�����Ѿ���ʼ���ɹ�,������δ�����ļ�ϵͳ�����ļ�ϵͳ��֧�� */
DEF_DISK_READY		EQU		010H			;/*�Ѿ��������̵��ļ�ϵͳ�����ܹ�֧�� */
DEF_DISK_OPEN_ROOT	EQU		012H			;/*�Ѿ��򿪸�Ŀ¼,ʹ�ú����ر�,ע��FAT12/FAT16��Ŀ¼�ǹ̶����� */
DEF_DISK_OPEN_DIR	EQU		013H			;/*�Ѿ�����Ŀ¼Ŀ¼(�ļ���) */
DEF_DISK_OPEN_FILE	EQU		014H			;/*�Ѿ����ļ� */
;#endif

;/********************************************************************************************************************** */
;/*�ļ�ϵͳ���ö��� */

;#ifndef	DEF_SECTOR_SIZE
DEF_SECTOR_SIZE		EQU		200H			;/*U�̻���SD��Ĭ�ϵ����������Ĵ�С */
;#endif

;#ifndef	DEF_WILDCARD_CHAR
DEF_WILDCARD_CHAR	EQU		02AH			;/*·������ͨ��� '*' */
DEF_SEPAR_CHAR1		EQU		05CH			;/*·�����ķָ��� '\' */
DEF_SEPAR_CHAR2		EQU		02FH			;/*·�����ķָ��� '/' */
DEF_FILE_YEAR		EQU		2004			;/*Ĭ���ļ�����: 2004�� */
DEF_FILE_MONTH		EQU		1				;/*Ĭ���ļ�����: 1�� */
DEF_FILE_DATE		EQU		1				;/*Ĭ���ļ�����: 1�� */
;#endif

;#ifndef	ATTR_DIRECTORY

;/*FAT���������ļ�Ŀ¼��Ϣ */
;typedef struct _FAT_DIR_INFO {
;	UINT8	DIR_Name[11];					;/*00H,�ļ���,��11�ֽ�,���㴦��ո� */
;	UINT8	DIR_Attr;						;/*0BH,�ļ�����,�ο������˵�� */
;	UINT8	DIR_NTRes;						;/*0CH */
;	UINT8	DIR_CrtTimeTenth;				;/*0DH,�ļ�������ʱ��,��0.1�뵥λ���� */
;	UINT16	DIR_CrtTime;					;/*0EH,�ļ�������ʱ�� */
;	UINT16	DIR_CrtDate;					;/*10H,�ļ����������� */
;	UINT16	DIR_LstAccDate;					;/*12H,���һ�δ�ȡ���������� */
;	UINT16	DIR_FstClusHI;					;/*14H */
;	UINT16	DIR_WrtTime;					;/*16H,�ļ��޸�ʱ��,�ο�ǰ��ĺ�MAKE_FILE_TIME */
;	UINT16	DIR_WrtDate;					;/*18H,�ļ��޸�����,�ο�ǰ��ĺ�MAKE_FILE_DATE */
;	UINT16	DIR_FstClusLO;					;/*1AH */
;	UINT32	DIR_FileSize;					;/*1CH,�ļ����� */
;} FAT_DIR_INFO, *P_FAT_DIR_INFO;			;/*20H */
FAT_DIR_INF_Name		EQU		000H		;/*00H,�ļ���,��11�ֽ�,���㴦��ո� */
FAT_DIR_INF_Attr		EQU		00BH		;/*0BH,�ļ�����,�ο������˵�� */
FAT_DIR_INF_NTRes		EQU		00CH		;/*0CH */
FAT_DIR_INF_CrtTimeTen	EQU		00DH		;/*0DH,�ļ�������ʱ��,��0.1�뵥λ���� */
FAT_DIR_INF_CrtTime		EQU		00EH		;/*0EH,�ļ�������ʱ�� */
FAT_DIR_INF_CrtDate		EQU		010H		;/*10H,�ļ����������� */
FAT_DIR_INF_LstAccDate	EQU		012H		;/*12H,���һ�δ�ȡ���������� */
FAT_DIR_INF_FstClusHI	EQU		014H		;/*14H */
FAT_DIR_INF_WrtTime		EQU		016H		;/*16H,�ļ��޸�ʱ��,�ο�ǰ��ĺ�MAKE_FILE_TIME */
FAT_DIR_INF_WrtDate		EQU		018H		;/*18H,�ļ��޸�����,�ο�ǰ��ĺ�MAKE_FILE_DATE */
FAT_DIR_INF_FstClusLO	EQU		01AH		;/*1AH */
FAT_DIR_INF_FileSize	EQU		01CH		;/*1CH,�ļ����� */
FAT_DIR_INF_STRUCT_SIZE	EQU		020H		;�ṹ��С

;/*�ļ����� */
ATTR_READ_ONLY			EQU		001H		;/*�ļ�Ϊֻ������ */
ATTR_HIDDEN				EQU		002H		;/*�ļ�Ϊ�������� */
ATTR_SYSTEM				EQU		004H		;/*�ļ�Ϊϵͳ���� */
ATTR_VOLUME_ID			EQU		008H		;/*���� */
ATTR_DIRECTORY			EQU		010H		;/*��Ŀ¼(�ļ���) */
ATTR_ARCHIVE			EQU		020H		;/*�ļ�Ϊ�浵���� */
ATTR_LONG_NAME			EQU		( ATTR_READ_ONLY | ATTR_HIDDEN | ATTR_SYSTEM | ATTR_VOLUME_ID )	;/*���ļ������� */
ATTR_LONG_NAME_MASK		EQU		( ATTR_LONG_NAME | ATTR_DIRECTORY | ATTR_ARCHIVE )
;/*�ļ����� UINT8 */
;/*bit0 bit1 bit2 bit3 bit4 bit5 bit6 bit7 */
;/* ֻ   ��   ϵ   ��   Ŀ   ��   δ����   */
;/* ��   ��   ͳ   ��   ¼   ��            */
;/*�ļ�ʱ�� UINT16 */
;/*Time = (Hour<<11) + (Minute<<5) + (Second>>1) */
;#define MAKE_FILE_TIME( h, m, s )	( (h<<11) + (m<<5) + (s>>1) )	;/*����ָ��ʱ������ļ�ʱ������ */
;/*�ļ����� UINT16 */
;/*Date = ((Year-1980)<<9) + (Month<<5) + Day */
;#define MAKE_FILE_DATE( y, m, d )	( ((y-1980)<<9) + (m<<5) + d )	;/*����ָ�������յ��ļ��������� */

LONE_NAME_MAX_CHAR		EQU		(255*2)		;/*���ļ�������ַ���/�ֽ��� */
LONG_NAME_PER_DIR		EQU		(13*2)		;/*���ļ�����ÿ���ļ�Ŀ¼��Ϣ�ṹ�е��ַ���/�ֽ��� */

;#endif

;/********************************************************************************************************************** */
;/*SCSI�����������������ṹ */

;#ifndef	SPC_CMD_INQUIRY

;/*SCSI������ */
SPC_CMD_INQUIRY			EQU		012H
SPC_CMD_READ_CAPACITY	EQU		025H
SPC_CMD_READ10			EQU		028H
SPC_CMD_WRITE10			EQU		02AH
SPC_CMD_TEST_READY		EQU		000H
SPC_CMD_REQUEST_SENSE	EQU		003H
SPC_CMD_MODESENSE6		EQU		01AH
SPC_CMD_MODESENSE10		EQU		05AH
SPC_CMD_START_STOP		EQU		01BH

;/*BulkOnlyЭ�������� */
;typedef struct _BULK_ONLY_CBW {
;	UINT32	CBW_Sig;
;	UINT32	CBW_Tag;
;	UINT8	CBW_DataLen0;					;/*08H,����: ���ݴ��䳤��,����������������Чֵ��0��48,���������������ЧֵΪ0��33 */
;	UINT8	CBW_DataLen1;
;	UINT16	CBW_DataLen2;
;	UINT8	CBW_Flag;						;/*0CH,����: ���䷽��ȱ�־,λ7Ϊ1����������,λΪ0��������ݻ���û������ */
;	UINT8	CBW_LUN;
;	UINT8	CBW_CB_Len;						;/*0EH,����: �����ĳ���,��Чֵ��1��16 */
;	UINT8	CBW_CB_Buf[16];					;/*0FH,����: �����,�û��������Ϊ16���ֽ� */
;} BULK_ONLY_CBW, *P_BULK_ONLY_CBW;			;/*BulkOnlyЭ��������, ����CBW�ṹ */
BO_CBW_DataLen0			EQU		008H		;/*08H,����: ���ݴ��䳤��,����������������Чֵ��0��48,���������������ЧֵΪ0��33 */
BO_CBW_Flag				EQU		00CH		;/*0CH,����: ���䷽��ȱ�־,λ7Ϊ1����������,λΪ0��������ݻ���û������ */
BO_CBW_CB_Len			EQU		00EH		;/*0EH,����: �����ĳ���,��Чֵ��1��16 */
BO_CBW_CB_Buf			EQU		00FH		;/*0FH,����: �����,�û��������Ϊ16���ֽ� */
BO_CBW_STRUCT_SIZE		EQU		01FH		;�ṹ��С

;/*INQUIRY����ķ������� */
;typedef struct _INQUIRY_DATA {
;	UINT8	DeviceType;					;/*00H, �豸���� */
;	UINT8	RemovableMedia;				;/*01H, λ7Ϊ1˵�����ƶ��洢 */
;	UINT8	Versions;					;/*02H, Э��汾 */
;	UINT8	DataFormatAndEtc;			;/*03H, ָ���������ݸ�ʽ */
;	UINT8	AdditionalLength;			;/*04H, �������ݵĳ��� */
;	UINT8	Reserved1;
;	UINT8	Reserved2;
;	UINT8	MiscFlag;					;/*07H, һЩ���Ʊ�־ */
;	UINT8	VendorIdStr[8];				;/*08H, ������Ϣ */
;	UINT8	ProductIdStr[16];			;/*10H, ��Ʒ��Ϣ */
;	UINT8	ProductRevStr[4];			;/*20H, ��Ʒ�汾 */
;} INQUIRY_DATA, *P_INQUIRY_DATA;		;/*24H */
INQUIRY_DeviceType		EQU		000H
INQUIRY_RemovableMedia	EQU		001H
INQUIRY_VendorIdStr		EQU		008H
INQUIRY_ProductIdStr	EQU		010H
INQUIRY_ProductRevStr	EQU		020H
INQUIRY_STRUCT_SIZE		EQU		024H		;�ṹ��С

;/*REQUEST SENSE����ķ������� */
;typedef struct _SENSE_DATA {
;	UINT8	ErrorCode;					;/*00H, ������뼰��Чλ */
;	UINT8	SegmentNumber;
;	UINT8	SenseKeyAndEtc;				;/*02H, ������ */
;	UINT8	Information0;
;	UINT8	Information1;
;	UINT8	Information2;
;	UINT8	Information3;
;	UINT8	AdditSenseLen;				;/*07H, �������ݵĳ��� */
;	UINT8	CmdSpecInfo[4];
;	UINT8	AdditSenseCode;				;/*0CH, ���Ӽ��� */
;	UINT8	AddSenCodeQual;				;/*0DH, ��ϸ�ĸ��Ӽ��� */
;	UINT8	FieldReplaUnit;
;	UINT8	SenseKeySpec[3];
;} SENSE_DATA, *P_SENSE_DATA;			;/*12H */

;#endif

;/********************************************************************************************************************** */
;/*�����ļ�ģʽ�µ��������������ṹ */

;#ifndef	MAX_FILE_NAME_LEN

MAX_FILE_NAME_LEN		EQU		(13+1)		;/*�ļ�����󳤶�,��󳤶���1����Ŀ¼��+8�����ļ���+1��С����+3��������+������=14 */

;/*������������ݺ�������� */
;typedef union _CH376_CMD_DATA {
;	struct {
;		UINT8	mBuffer[ MAX_FILE_NAME_LEN ];
;	} Default;
;
;	INQUIRY_DATA	DiskMountInq;			;/*����: INQUIRY����ķ������� */
;											;/*CMD0H_DISK_MOUNT: ��ʼ�����̲����Դ����Ƿ����,�״�ִ��ʱ */
;
;	FAT_DIR_INFO	OpenDirInfo;			;/*����: ö�ٵ����ļ�Ŀ¼��Ϣ */
;											;/*CMD0H_FILE_OPEN: ö���ļ���Ŀ¼(�ļ���) */
;
;	FAT_DIR_INFO	EnumDirInfo;			;/*����: ö�ٵ����ļ�Ŀ¼��Ϣ */
;											;/*CMD0H_FILE_ENUM_GO: ����ö���ļ���Ŀ¼(�ļ���) */
;
;	struct {
;		UINT8	mUpdateFileSz;				;/*�������: �Ƿ����������ļ�����, 0���ֹ���³��� */
;	} FileCLose;							;/*CMD1H_FILE_CLOSE: �رյ�ǰ�Ѿ��򿪵��ļ� */
;
;	struct {
;		UINT8	mDirInfoIndex;				;/*�������: ָ����Ҫ��ȡ��Ŀ¼��Ϣ�ṹ�������ڵ�������, 0FFH��Ϊ��ǰ�Ѿ��򿪵��ļ� */
;	} DirInfoRead;							;/*CMD1H_DIR_INFO_READ: ��ȡ�ļ���Ŀ¼��Ϣ */
;
;	union {
;		UINT32	mByteOffset;				;/*�������: ƫ���ֽ���,���ֽ�Ϊ��λ��ƫ����(�ܳ���32λ,���ֽ���ǰ) */
;		UINT32	mSectorLba;					;/*����: ��ǰ�ļ�ָ���Ӧ�ľ�������������,0FFFFFFFFH���ѵ��ļ�β(�ܳ���32λ,���ֽ���ǰ) */
;	} ByteLocate;							;/*CMD4H_BYTE_LOCATE: ���ֽ�Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
;
;	struct {
;		UINT16	mByteCount;					;/*�������: �����ȡ���ֽ���(�ܳ���16λ,���ֽ���ǰ) */
;	} ByteRead;								;/*CMD2H_BYTE_READ: ���ֽ�Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
;
;	struct {
;		UINT16	mByteCount;					;/*�������: ����д����ֽ���(�ܳ���16λ,���ֽ���ǰ) */
;	} ByteWrite;							;/*CMD2H_BYTE_WRITE: ���ֽ�Ϊ��λ��ǰλ��д�����ݿ� */
;
;	union {
;		UINT32	mSectorOffset;				;/*�������: ƫ��������,������Ϊ��λ��ƫ����(�ܳ���32λ,���ֽ���ǰ) */
;		UINT32	mSectorLba;					;/*����: ��ǰ�ļ�ָ���Ӧ�ľ�������������,0FFFFFFFFH���ѵ��ļ�β(�ܳ���32λ,���ֽ���ǰ) */
;	} SectorLocate;							;/*CMD4H_SEC_LOCATE: ������Ϊ��λ�ƶ���ǰ�ļ�ָ�� */
;
;	struct {
;		UINT8	mSectorCount;				;/*�������: �����ȡ�������� */
;											;/*����: ������ȡ�������� */
;		UINT8	mReserved1;
;		UINT8	mReserved2;
;		UINT8	mReserved3;
;		UINT32	mStartSector;				;/*����: ������ȡ�����������ʼ��������������(�ܳ���32λ,���ֽ���ǰ) */
;	} SectorRead;							;/*CMD1H_SEC_READ: ������Ϊ��λ�ӵ�ǰλ�ö�ȡ���ݿ� */
;
;	struct {
;		UINT8	mSectorCount;				;/*�������: ����д��������� */
;											;/*����: ����д��������� */
;		UINT8	mReserved1;
;		UINT8	mReserved2;
;		UINT8	mReserved3;
;		UINT32	mStartSector;				;/*����: ����д������������ʼ��������������(�ܳ���32λ,���ֽ���ǰ) */
;	} SectorWrite;							;/*CMD1H_SEC_WRITE: ������Ϊ��λ�ڵ�ǰλ��д�����ݿ� */
;
;	struct {
;		UINT32	mDiskSizeSec;				;/*����: �����������̵���������(�ܳ���32λ,���ֽ���ǰ) */
;	} DiskCapacity;							;/*CMD0H_DISK_CAPACITY: ��ѯ������������ */
;
;	struct {
;		UINT32	mTotalSector;				;/*����: ��ǰ�߼��̵���������(�ܳ���32λ,���ֽ���ǰ) */
;		UINT32	mFreeSector;				;/*����: ��ǰ�߼��̵�ʣ��������(�ܳ���32λ,���ֽ���ǰ) */
;		UINT8	mDiskFat;					;/*����: ��ǰ�߼��̵�FAT����,1-FAT12,2-FAT16,3-FAT32 */
;	} DiskQuery;							;/*CMD_DiskQuery, ��ѯ������Ϣ */
;
;	BULK_ONLY_CBW	DiskBocCbw;				;/*�������: CBW����ṹ */
;											;/*CMD0H_DISK_BOC_CMD: ��USB�洢��ִ��BulkOnly����Э������� */
;
;	struct {
;		UINT8	mMaxLogicUnit;				;/*����: USB�洢��������߼���Ԫ�� */
;	} DiskMaxLun;							;/*CMD0H_DISK_MAX_LUN: ���ƴ���-��ȡUSB�洢������߼���Ԫ�� */
;
;	INQUIRY_DATA	DiskInitInq;			;/*����: INQUIRY����ķ������� */
;											;/*CMD0H_DISK_INIT: ��ʼ��USB�洢�� */
;
;	INQUIRY_DATA	DiskInqData;			;/*����: INQUIRY����ķ������� */
;											;/*CMD0H_DISK_INQUIRY: ��ѯUSB�洢������ */
;
;	SENSE_DATA		ReqSenseData;			;/*����: REQUEST SENSE����ķ������� */
;											;/*CMD0H_DISK_R_SENSE: ���USB�洢������ */
;
;	struct {
;		UINT32	mDiskSizeSec;				;/*����: �����������̵���������(�ܳ���32λ,���ֽ���ǰ) */
;	} DiskSize;								;/*CMD0H_DISK_SIZE: ��ȡUSB�洢�������� */
;
;	struct {
;		UINT32	mStartSector;				;/*�������: LBA������ַ(�ܳ���32λ,���ֽ���ǰ) */
;		UINT8	mSectorCount;				;/*�������: �����ȡ�������� */
;	} DiskRead;								;/*CMD5H_DISK_READ: ��USB�洢�������ݿ�(������Ϊ��λ) */
;
;	struct {
;		UINT32	mStartSector;				;/*�������: LBA������ַ(�ܳ���32λ,���ֽ���ǰ) */
;		UINT8	mSectorCount;				;/*�������: ����д��������� */
;	} DiskWrite;							;/*CMD5H_DISK_WRITE: ��USB�洢��д���ݿ�(������Ϊ��λ) */
;} CH376_CMD_DATA, *P_CH376_CMD_DATA;

;#endif

;/********************************************************************************************************************** */
;/*�����ļ�ģʽ�µ��ļ�ϵͳ�����ĵ�ַ */

;#ifndef	VAR_FILE_SIZE

;/*8λ/���ֽڱ��� */
VAR_SYS_BASE_INFO	EQU		020H			;/*��ǰϵͳ�Ļ�����Ϣ */
;/*          λ6����ָʾUSB�洢�豸�������SubClass-Code, λ6Ϊ0��˵�������Ϊ6, λ6Ϊ1��˵��������Ƿ�6������ֵ */
;/*          λ5����ָʾUSB�豸��ʽ�µ�USB����״̬��USB������ʽ�µ�USB�豸����״̬ */
;/*               USB�豸��ʽ��, λ5Ϊ1��USB�������, λ5λ0����δ���� */
;/*               USB������ʽ��, λ5Ϊ1��USB�˿ڴ���USB�豸, λ5λ0��USB�˿�û��USB�豸 */
;/*          λ4����ָʾUSB�豸��ʽ�µĻ���������״̬, λ4Ϊ1��˵��USB��������������״̬, λ6Ϊ1��˵���Ѿ��ͷ� */
;/*          ����λ, ����,�����޸� */
VAR_RETRY_TIMES		EQU		025H			;/*USB������������Դ��� */
;/*          λ7Ϊ0���յ�NAKʱ������, λ7Ϊ1λ6Ϊ0���յ�NAKʱ��������(������CMD_ABORT_NAK�����������), λ7Ϊ1λ6Ϊ1���յ�NAKʱ�������3�� */
;/*          λ5~λ0Ϊ��ʱ������Դ��� */
VAR_FILE_BIT_FLAG	EQU		026H			;/*�����ļ�ģʽ�µ�λ��־ */
;/*          λ1��λ0, �߼��̵�FAT�ļ�ϵͳ��־, 00-FAT12, 01-FAT16, 10-FAT32, 11-�Ƿ� */
;/*          λ2, ��ǰ�������е�FAT�������Ƿ��޸ı�־, 0-δ�޸�, 1-���޸� */
;/*          λ3, �ļ�������Ҫ�޸ı�־, ��ǰ�ļ���׷������, 0-δ׷�������޸�, 1-��׷����Ҫ�޸� */
;/*          ����λ, ����,�����޸� */
VAR_DISK_STATUS		EQU		02BH			;/*�����ļ�ģʽ�µĴ��̼��ļ�״̬ */
VAR_SD_BIT_FLAG		EQU		030H			;/*�����ļ�ģʽ��SD����λ��־ */
;/*          λ0, SD���汾, 0-ֻ֧��SD��һ��,1-֧��SD�ڶ��� */
;/*          λ1, �Զ�ʶ��, 0-SD��, 1-MMC�� */
;/*          λ2, �Զ�ʶ��, 0-��׼����SD��, 1-������SD��(HC-SD) */
;/*          λ4, ACMD41���ʱ */
;/*          λ5, CMD1���ʱ */
;/*          λ6, CMD58���ʱ */
;/*          ����λ, ����,�����޸� */
VAR_UDISK_TOGGLE	EQU		031H			;/*USB�洢�豸��BULK-IN/BULK-OUT�˵��ͬ����־ */
;/*          λ7, Bulk-In�˵��ͬ����־ */
;/*          λ6, Bulk-In�˵��ͬ����־ */
;/*          λ5~λ0, ����Ϊ0 */
VAR_UDISK_LUN		EQU		034H			;/*USB�洢�豸���߼���Ԫ�� */
;/*          λ7~λ4, USB�洢�豸�ĵ�ǰ�߼���Ԫ��,CH376��ʼ��USB�洢�豸��,Ĭ���Ƿ���0#�߼���Ԫ */
;/*          λ3~λ0, USB�洢�豸������߼���Ԫ��,��1������߼���Ԫ�� */
VAR_SEC_PER_CLUS	EQU		038H			;/*�߼��̵�ÿ�������� */
VAR_FILE_DIR_INDEX	EQU		03BH			;/*��ǰ�ļ�Ŀ¼��Ϣ�������ڵ������� */
VAR_CLUS_SEC_OFS	EQU		03CH			;/*��ǰ�ļ�ָ���ڴ��ڵ�����ƫ��,Ϊ0xFF��ָ���ļ�ĩβ,�ؽ��� */

;/*32λ/4�ֽڱ��� */
VAR_DISK_ROOT		EQU		044H			;/*����FAT16��Ϊ��Ŀ¼ռ��������,����FAT32��Ϊ��Ŀ¼��ʼ�غ�(�ܳ���32λ,���ֽ���ǰ) */
VAR_DSK_TOTAL_CLUS	EQU		048H			;/*�߼��̵��ܴ���(�ܳ���32λ,���ֽ���ǰ) */
VAR_DSK_START_LBA	EQU		04CH			;/*�߼��̵���ʼ����������LBA(�ܳ���32λ,���ֽ���ǰ) */
VAR_DSK_DAT_START	EQU		050H			;/*�߼��̵������������ʼLBA(�ܳ���32λ,���ֽ���ǰ) */
VAR_LBA_BUFFER		EQU		054H			;/*��ǰ�������ݻ����������ݶ�Ӧ��LBA(�ܳ���32λ,���ֽ���ǰ) */
VAR_LBA_CURRENT		EQU		058H			;/*��ǰ��д�Ĵ�����ʼLBA��ַ(�ܳ���32λ,���ֽ���ǰ) */
VAR_FAT_DIR_LBA		EQU		05CH			;/*��ǰ�ļ�Ŀ¼��Ϣ���ڵ�����LBA��ַ(�ܳ���32λ,���ֽ���ǰ) */
VAR_START_CLUSTER	EQU		060H			;/*��ǰ�ļ�����Ŀ¼(�ļ���)����ʼ�غ�(�ܳ���32λ,���ֽ���ǰ) */
VAR_CURRENT_CLUST	EQU		064H			;/*��ǰ�ļ��ĵ�ǰ�غ�(�ܳ���32λ,���ֽ���ǰ) */
VAR_FILE_SIZE		EQU		068H			;/*��ǰ�ļ��ĳ���(�ܳ���32λ,���ֽ���ǰ) */
VAR_CURRENT_OFFSET	EQU		06CH			;/*��ǰ�ļ�ָ��,��ǰ��дλ�õ��ֽ�ƫ��(�ܳ���32λ,���ֽ���ǰ) */

;#endif

;/********************************************************************************************************************** */
;/*����USB���� */

;/*USB�İ���ʶPID, ������ʽ�����õ� */
;#ifndef	DEF_USB_PID_SETUP
DEF_USB_PID_NULL	EQU		000H			;/*����PID, δ���� */
DEF_USB_PID_SOF		EQU		005H
DEF_USB_PID_SETUP	EQU		00DH
DEF_USB_PID_IN		EQU		009H
DEF_USB_PID_OUT		EQU		001H
DEF_USB_PID_ACK		EQU		002H
DEF_USB_PID_NAK		EQU		00AH
DEF_USB_PID_STALL	EQU		00EH
DEF_USB_PID_DATA0	EQU		003H
DEF_USB_PID_DATA1	EQU		00BH
DEF_USB_PID_PRE		EQU		00CH
;#endif

;/*USB��������, ���ù̼�ģʽ�����õ� */
;#ifndef	DEF_USB_REQ_TYPE
DEF_USB_REQ_READ	EQU		080H			;/*���ƶ����� */
DEF_USB_REQ_WRITE	EQU		000H			;/*����д���� */
DEF_USB_REQ_TYPE	EQU		060H			;/*������������ */
DEF_USB_REQ_STAND	EQU		000H			;/*��׼���� */
DEF_USB_REQ_CLASS	EQU		020H			;/*�豸������ */
DEF_USB_REQ_VENDOR	EQU		040H			;/*�������� */
DEF_USB_REQ_RESERVE	EQU		060H			;/*�������� */
;#endif

;/*USB��׼�豸����, RequestType��λ6λ5=00(Standard), ���ù̼�ģʽ�����õ� */
;#ifndef	DEF_USB_GET_DESCR
DEF_USB_CLR_FEATURE	EQU		001H
DEF_USB_SET_FEATURE	EQU		003H
DEF_USB_GET_STATUS	EQU		000H
DEF_USB_SET_ADDRESS	EQU		005H
DEF_USB_GET_DESCR	EQU		006H
DEF_USB_SET_DESCR	EQU		007H
DEF_USB_GET_CONFIG	EQU		008H
DEF_USB_SET_CONFIG	EQU		009H
DEF_USB_GET_INTERF	EQU		00AH
DEF_USB_SET_INTERF	EQU		00BH
DEF_USB_SYNC_FRAME	EQU		00CH
;#endif

;/********************************************************************************************************************** */
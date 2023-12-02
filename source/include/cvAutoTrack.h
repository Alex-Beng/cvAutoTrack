#pragma once
#ifdef CVAUTOTRACK_EXPORTS
#define CVAUTOTRACK_PORT __declspec(dllexport)
#else
#define CVAUTOTRACK_PORT __declspec(dllimport)
#endif
#define CVAUTOTRACK_CALL __stdcall
#define CVAUTOTRACK_API CVAUTOTRACK_PORT CVAUTOTRACK_CALL

/// @brief ��Դ��ʼ��
/// @return ��ʼ��״̬
extern "C" bool CVAUTOTRACK_API InitResource();
/// @brief ж����Դ
/// @return �Ƿ�ж�سɹ�
extern "C" bool CVAUTOTRACK_API UnInitResource();

/// @brief ����ѭ�����÷���
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API StartServer();
/// @brief ֹͣѭ�����÷���
/// @return ֹͣ�ɹ�
extern "C" bool CVAUTOTRACK_API StopServer();
/// @brief ѭ�����ü��
/// @param interval_ms ���ʱ��
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetServerInterval(int interval_ms);
/// @brief ����ѭ�����ûص�����
/// @param callback �ص�����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetServerCallback(void (*callback)(const char *json_buff, int buff_size));

/// @brief ���ý�����־�ļ�
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetDisableFileLog();
/// @brief ����������־�ļ�
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetEnableFileLog();
/// @brief ������־�ļ�·��
/// @param path ·�������·�������ڻ��Զ�������Ĭ��Ϊ��ǰĿ¼
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetLogFilePath(const char *path);
/// @brief ������־�ļ���
/// @param name �ļ�����Ĭ��ΪcvAutoTrack.log
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetLogFileName(const char *name);
/// @brief ����ʹ��Bitblt��ͼģʽ
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetUseBitbltCaptureMode();
/// @brief ����ʹ��WidnowsGraphicsCaphics��ͼģʽ
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetUseGraphicsCaptureMode();
/// @brief ����ʹ��Dwm��ͼģʽ
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetUseDwmCaptureMode();
/// @brief ���òɼ����
/// @param handle ���������0���Զ�Ѱ�Ҿ��
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetCaptureHandle(long long int handle);
/// @brief ���òɼ�����ص�����
/// @param callback �ص�����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetCaptureHandleCallback(long long int (*callback)());
/// @brief ����ʹ�ñ���ͼƬ��ͼģʽ
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetUseLocalImageCaptureMode();
/// @brief �����Ӵ�Դ�ص�����
/// @param callback �ص�����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetScreenSourceCallback(void (*callback)(const char *image_encode_data, int image_data_size));
/// @brief �����Ӵ�Դ�ص�������չ
/// @param callback �ص�����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetScreenSourceCallbackEx(void (*callback)(const char *image_data, int image_width, int image_height, int image_channels));
/// @brief �����Ӵ�ԴͼƬ
/// @param image_encode_data ͼƬ�ļ�����������
/// @param image_data_size ͼƬ�ļ����������ݴ�С
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetScreenSourceImage(const char *image_encode_data, int image_data_size);
/// @brief �����Ӵ�ԴͼƬ��չ
/// @param image_data ͼƬ����ָ��
/// @param image_width ͼƬ���
/// @param image_height ͼƬ�߶�
/// @param image_channels ͼƬͨ����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetScreenSourceImageEx(const char *image_data, int image_width, int image_height, int image_channels);
/// @brief �����Ӵ��ͻ���λ�ûص����������ڲü������Ӵ�Դ
/// @param callback �ص�����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetScreenClientRectCallback(void (*callback)(int &x, int &y, int &width, int &height));

/// @brief ���û���·��
/// @param path ����·����Ĭ��Ϊ��ǰĿ¼
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetTrackCachePath(const char *path);
/// @brief ���û����ļ���
/// @param name �ļ�����Ĭ��ΪcvAutoTrack.Cache
/// @return �ҵ������ļ�
extern "C" bool CVAUTOTRACK_API SetTrackCacheName(const char *name);
/// @brief ������������ԭ��
/// @param x ԭ��x����
/// @param y ԭ��y����
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetWorldCenter(double x, double y);
/// @brief ����������������
/// @param scale ���ű���
/// @return ���óɹ�
extern "C" bool CVAUTOTRACK_API SetWorldScale(double scale);

extern "C" bool CVAUTOTRACK_API ImportMapBlock(int uuid, const char *image_encode_data, int image_data_size);
extern "C" bool CVAUTOTRACK_API ImportMapBlockData(int uuid, const char *image_data, int image_width, int image_height, int image_channels);
extern "C" bool CVAUTOTRACK_API ImportMapBlockCenter(int uuid, int x, int y);
extern "C" bool CVAUTOTRACK_API ImportMapBlockRelativeCenter(int uuid, int parent_uuid, int x, int y);
extern "C" bool CVAUTOTRACK_API ImportMapBlockCenterScale(int uuid, int x, int y, double scale);
extern "C" bool CVAUTOTRACK_API ImportMapBlockRelativeCenterScale(int uuid, int parent_uuid, int x, int y, double scale);

extern "C" bool CVAUTOTRACK_API GetTransformOfMap(double &x, double &y, double &a, int &mapId);
extern "C" bool CVAUTOTRACK_API GetPositionOfMap(double &x, double &y, int &mapId);
extern "C" bool CVAUTOTRACK_API GetDirection(double &a);
extern "C" bool CVAUTOTRACK_API GetRotation(double &a);
extern "C" bool CVAUTOTRACK_API GetStar(double &x, double &y, bool &isEnd);
extern "C" bool CVAUTOTRACK_API GetStarJson(char *json_buff, int buff_size);
extern "C" bool CVAUTOTRACK_API GetUID(int &uid);
extern "C" bool CVAUTOTRACK_API GetAllInfo(double &x, double &y, int &mapId, double &a, double &r, int &uid);

extern "C" bool CVAUTOTRACK_API GetInfoLoadPicture(const char *path, int &uid, double &x, double &y, double &a);
extern "C" bool CVAUTOTRACK_API GetInfoLoadVideo(const char *path, const char *out_path);

extern "C" bool CVAUTOTRACK_API DebugCapture();
extern "C" bool CVAUTOTRACK_API DebugCapturePath(const char *path);

extern "C" int CVAUTOTRACK_API GetLastErr();
extern "C" int CVAUTOTRACK_API GetLastErrMsg(char *msg_buff, int buff_size);
extern "C" int CVAUTOTRACK_API GetLastErrJson(char *json_buff, int buff_size);

extern "C" bool CVAUTOTRACK_API GetCompileVersion(char *version_buff, int buff_size);
extern "C" bool CVAUTOTRACK_API GetCompileTime(char *time_buff, int buff_size);

extern "C" bool CVAUTOTRACK_API GetMapIsEmbedded();
/// @brief 
/// @param doc_buff 
/// @param buff_size 
/// @return 
extern "C" bool CVAUTOTRACK_API GetHelpDoc(char *doc_buff, int buff_size);

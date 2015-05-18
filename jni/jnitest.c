#include <com_vless_MainActivity.h>
#include <stdio.h>
#include <pthread.h>
pthread_t id;

//jni
JavaVM * gs_jvm;
jobject jobj;
JNIEnv *jenv = NULL;
jclass jcls;
jmethodID jmthid;
void thread(void)
{
	__android_log_print(4, "feihui", "this is in thread");
	int status = (*gs_jvm)->GetEnv(gs_jvm, (void **) &jenv, JNI_VERSION_1_6);
	if (status < 0)
	{
		__android_log_print(4, "feihui", "this is in thread2");
		status = (*gs_jvm)->AttachCurrentThread(gs_jvm, &jenv, NULL);
		if (status < 0)
		{
			__android_log_print(4, "feihui", "getEnv faild");
		}
	}
	jcls = (*jenv)->GetObjectClass(jenv, jobj);
	jmthid = (*jenv)->GetMethodID(jenv, jcls, "callbackinthread", "(I)V");
	(*jenv)->CallVoidMethod(jenv, jobj, jmthid, 100);
	(*jenv)->DeleteLocalRef(jenv, jcls);
	(*gs_jvm)->DetachCurrentThread(gs_jvm);

}
JNIEXPORT jstring JNICALL Java_com_vless_MainActivity_getIntC2Java(JNIEnv *env, jobject jthiz)
{

	//得到类中的全局变量，然后赋值
//	jclass clazz = (*env)->FindClass(env, "com/vless/MainActivity");
	jclass clazz = (*env)->GetObjectClass(env, jthiz); //此方法和上面的方法是一样的
	jfieldID id_ = (*env)->GetFieldID(env, clazz, "mint", "I");
	jint id = (*env)->GetIntField(env, jthiz, id_);
	(*env)->SetIntField(env, jthiz, id_, 200);

	//回调java中的额方法void callback(int num),
	//注意：方法签名中(I)V,括号总的I表示方法中的参数个数，本例中有一个参数ｎｕｍ
	jmethodID mid = (*env)->GetMethodID(env, clazz, "callback", "(I)V");
	(*env)->CallVoidMethod(env, jthiz, mid, 20);

	//让env变成全局变量
	jobj = (*env)->NewGlobalRef(env, jthiz);
	//得到ｊｖｍ
	(*env)->GetJavaVM(env, &gs_jvm);
	//创建新线程
//	pthread_t id;
	int i, ret;
	ret = pthread_create(&id, NULL, (void *) thread, NULL);
	if (ret != 0)
	{
		__android_log_print(4, "feihui", "this is in main");
	}

	__android_log_print(4, "feihui", "this is in main");
	pthread_join(id, NULL);

	return (*env)->NewStringUTF(env, "C2Java");
}

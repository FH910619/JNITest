package com.vless;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

public class MainActivity extends Activity
{
	static
	{
		System.loadLibrary("jnitest");
	}
	public int			mint;
	public static int	sint;

	public native String getIntC2Java();

	public native void C2Java();

	public native static void SC2Java();

	public void callbackC2Jave(int num)
	{
		Log.d("feihui", "num" + num);
	}

	public void callback(int num)
	{
		Log.d("feihui", "call java" + num);
	}

	public void callbackinthread(int num)
	{
		Log.d("feihui", "call java in thread" + num);
	}

	public int java2C()
	{
		return 0;
	}

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		Handler handler = new Handler();
		handler.postDelayed(new Runnable()
		{

			@Override
			public void run()
			{
				Log.d("feihui", getIntC2Java() + "mint" + mint);
			}
		}, 1000);

	}
}

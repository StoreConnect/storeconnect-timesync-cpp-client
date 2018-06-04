package com.ubudu.serverdate;

import android.content.Context;
import android.os.Handler;
import android.util.Log;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.RequestFuture;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.ubudu.serverdate.core.http_get_interface;
import com.ubudu.serverdate.core.server_date;
import com.ubudu.serverdate.core.server_date_native_WrapperConstants;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ExecutionException;

public class ServerDate  {

    public static final String TAG = ServerDate.class.getCanonicalName();

    static  {
        System.loadLibrary("server_date_native_Wrapper");
    }

    private server_date myServerDate;
    private RequestQueue requestQueue;
    private http_get_interface http_get_interface;

    public ServerDate(final String serverUrl, final Context context) {

        requestQueue = Volley.newRequestQueue(context);

        http_get_interface = new http_get_interface() {

            @Override
            public String get(String url) {
                RequestFuture<String> future = RequestFuture.newFuture();
                requestQueue.add(new StringRequest(Request.Method.GET, url, future, future));
                try {
                    return new JSONObject(future.get()).getString("time_now_millis");
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (ExecutionException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                return server_date_native_WrapperConstants.ERROR;
            }
        };

        myServerDate = new server_date(serverUrl,10,5, http_get_interface);
    }

    public void start() {
        myServerDate.offset_amortization_enabled(true);
        myServerDate.auto_synchronize();
        final Handler mHandler = new Handler();
        mHandler.post(new Runnable() {
            @Override
            public void run() {
                Log.i(TAG,"server_now: " +myServerDate.now());
                mHandler.postDelayed(this,10000);
            }
        });
    }

    public void stop() {
        myServerDate.stop_auto_synchronize();
    }

    public long now() {
        return myServerDate.now();
    }
}

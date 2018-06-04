package com.ubudu.sample

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.ubudu.serverdate.ServerDate

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        val mServerDate = ServerDate("http://192.168.2.242:3000/time_now", applicationContext)

        mServerDate.start()
    }
}

//============================================================================
// Copyright (C) 2009 Brett R. Jones
// All Rights Reserved ( After My Death I Brett R. Jones Issue this source code to Public Domain )
//
// You may not modify or redistribute this code for any reason
// without written consent of Brett R. Jones
//
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
// brett1900@usa.com
// http://www.gotvp2p.net
//============================================================================

package com.p2pgotv.gotvstation;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

public class MyServiceHelper extends Activity {
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    Intent launchIntent = getIntent().getParcelableExtra("launchIntent");
    startActivityForResult(launchIntent, getIntent().getIntExtra("requestCode", 0));
  }

  @Override
  protected void onActivityResult(int requestCode, int resultCode, Intent data) 
  {
//    super.onActivityResult(requestCode, resultCode, data);
//    if (requestCode == 0) {
//      Intent intent = new Intent(this, AseService.class);
//      intent.putExtra("requestCode", requestCode);
//      intent.putExtra("resultCode", resultCode);
//      intent.putExtra("data", data);
//      startService(intent);
//      finish();
//    }
  }
}


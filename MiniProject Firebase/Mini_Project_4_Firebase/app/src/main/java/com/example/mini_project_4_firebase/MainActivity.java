package com.example.mini_project_4_firebase;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.CompoundButton;
import com.google.firebase.database.*;

public class MainActivity extends AppCompatActivity {
    private TextView txtSuhu;
    private TextView txtSuhuValue;
    private TextView txtSudut;
    private EditText editTextSudut;
    private Button button;
    private Button buttonSistem;
    private boolean sistem = true;
    DatabaseReference myRefServo;
    DatabaseReference myRefSuhu;
    DatabaseReference myRefSistem;
    FirebaseDatabase database;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        myRefServo = database.getReference("Servo");
        myRefSuhu = database.getReference("Suhu");
        myRefSistem = database.getReference("Sistem");
        txtSuhuValue = findViewById(R.id.txtSuhuValue);
        editTextSudut = findViewById(R.id.editTxtSudut);
        buttonSistem = findViewById(R.id.buttonSistem);
        button = findViewById(R.id.button);
        button.setOnClickListener(v -> onClickBtnUbahSudut(v));
        buttonSistem.setOnClickListener(v -> onClickBtnSistem(v));
        ValueEventListener postListener = new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                txtSuhuValue.setText( dataSnapshot.getValue().toString());
            }

            @Override
            public void onCancelled(DatabaseError databaseError) {
                // Getting Post failed, log a message
                // ...
            }
        };
        myRefSuhu.addValueEventListener(postListener);
    }

    private void onClickBtnUbahSudut(View v) {
        Toast.makeText(getApplicationContext(), "Button Ubah Sudut di Tekan", Toast.LENGTH_LONG).show();
        if (sistem) {
            int tampSudut = Integer.parseInt(editTextSudut.getText().toString());
            myRefServo.setValue(tampSudut);
        }
    }

    private void onClickBtnSistem(View v){
        Toast.makeText(getApplicationContext(), "Button ON/OFF Sistem di Tekan", Toast.LENGTH_LONG).show();
        if(sistem){
            myRefSistem.setValue(1);
            sistem= !sistem; // Jika sistem True di ubah ke False
        } else{
            myRefSistem.setValue(0);
            sistem =!sistem; // Jika sistem False di ubah ke true
        }
    }


}




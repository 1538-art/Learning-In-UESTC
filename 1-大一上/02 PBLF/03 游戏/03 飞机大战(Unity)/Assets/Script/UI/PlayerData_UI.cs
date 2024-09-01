using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerData_UI : MonoBehaviour
{
    private string PlayerName;
    private string PlayerID;
    public Text PlayerData;
    public InputManager InputManager;
    // Start is called before the first frame update
    void Start()
    {
        //InputManager = GameObject.Find("DataInput").GetComponent<InputManager>();
        PlayerPrefs.DeleteKey("PlayerName");
    }

    // Update is called once per frame
    void Update()
    {
        PlayerName = InputManager.playername;
        //PlayerID = InputManager.playerid;
        PlayerData.text = "Íæ¼ÒÃû:" + PlayerName + "\n" ;
    }
}

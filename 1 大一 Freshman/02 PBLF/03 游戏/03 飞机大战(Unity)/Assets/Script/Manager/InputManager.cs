using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class InputManager : MonoBehaviour
{
    public InputField PlayerName;

    public string playername;

    // Start is called before the first frame update
    void Start()
    {
        
        PlayerName.onValueChange.AddListener(OnInputValueChanged_Name);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnInputValueChanged_Name(string txet)
    {
        playername = txet;
    }

   
}

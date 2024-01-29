using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Blood_UI : MonoBehaviour
{
    public Image Blood;
    public PlayerController Player;
    public float player_health_max;
    public float player_health;
    // Start is called before the first frame update
    void Start()
    {
        player_health_max = Player.maxhealth;
    }

    // Update is called once per frame
    void Update()
    {
        player_health = Player.health;
        Blood.fillAmount = player_health / player_health_max;
    }
}

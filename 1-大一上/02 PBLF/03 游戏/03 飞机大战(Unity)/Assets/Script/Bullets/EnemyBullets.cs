using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class EnemyBullets : MonoBehaviour
{
    public GameObject Player;
    private Rigidbody2D rigidbody;
    public float bullet_speed;
    private float bullet_life;
    // Start is called before the first frame update
    void Start()
    {
        Player = GameObject.Find("Player");
        rigidbody = GetComponent<Rigidbody2D>();
        if (Player != null)
        { 
            rigidbody .velocity  = Forecast(Player, 5, bullet_speed) * bullet_speed ; 
        }

    }

    // Update is called once per frame
    void Update()
    {
        bullet_life += Time.deltaTime;
        if (bullet_life > 8) Destroy(gameObject);
    }

    Vector2 Forecast(GameObject Player,int interaction,float bullet_speed)
    {
        float t;
        Vector2 aim_pos = Player.transform .position ;
        Vector2 my_pos = gameObject .transform .position ;
        Rigidbody2D rigidbody_player = Player.GetComponent<Rigidbody2D>();
        Vector2 targetVelocity = rigidbody_player.velocity;        
        t = (aim_pos- my_pos).magnitude / bullet_speed;
        for (int i=0;i < interaction ;i++)
        {
            aim_pos = (Vector2)Player.transform.position + t * targetVelocity;
            t = Vector2.Distance(aim_pos, my_pos) / bullet_speed;
        }

        return (aim_pos-my_pos).normalized;
    }
}

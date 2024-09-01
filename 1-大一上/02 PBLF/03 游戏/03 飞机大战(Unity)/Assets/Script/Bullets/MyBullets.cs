using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MyBullets : MonoBehaviour
{
    [Header ("Class")]
    public Rigidbody2D rigidbody;

    [Header ("BulletData")]
    public float my_bullet_speed;
    public float bullet_life;
    public int Damage;
    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        rigidbody.velocity = new Vector2(0f, my_bullet_speed);
    }

    // Update is called once per frame
    void Update()
    {
        bullet_life += Time.deltaTime;
        if (bullet_life >= 6f) Destroy(gameObject);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision .gameObject.layer == 6)//Enemy
        {
            Destroy(gameObject);
        }
    }
}

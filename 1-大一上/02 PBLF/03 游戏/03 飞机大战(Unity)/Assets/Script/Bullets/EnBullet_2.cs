using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnBullet_2 : MonoBehaviour
{
    private Rigidbody2D rigidbody;

    public Vector2 velocity;

    public float bullet_life;
    private float timer;
    void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        rigidbody.velocity = velocity;
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if (timer > bullet_life)
        {
            Destroy(gameObject);
        }
    }
}

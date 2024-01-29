using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet_Plus : MonoBehaviour
{
    public Rigidbody2D rigidbody;
    public Vector2 velocity;
    // Start is called before the first frame update
    void Start()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        rigidbody.velocity = velocity;
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

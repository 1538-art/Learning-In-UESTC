using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [Header("Class")]
    public GameObject Player_bullet;
    public Rigidbody2D myrigidbody;
    public Animator animator;
    public GameObject Dead_UI;

    [Header ("Enemy")]
    private Enemy_1 Enemy_1;
    private Enemy_2 Enemy_2;
    private Enemy_3 Enemy_3;
    private Enemy_4 Enemy_4;
        

    [Header("Health")]
    public float health;
    public float maxhealth;
    public int health_recover;
    public int collision_damage;

    [Header ("EnemyBulletData")]
    //ebd>> short for enemybullet_damage
    private int ebd_1;
    private int ebd_2;
    private int ebd_3;
    private int ebd_4;

    public int attack_type = 1;

    public bool isdead;
    [Header("Velocity")]
    public float move_direction_x;
    public float move_direction_y;
    public float velocity;
    
    private float timer = -100;
    [Header("BulletPosCorrection")]
    public Vector3 correction_1;
    public Vector3 correction_2;
    public Vector3 correction_3;
    // Start is called before the first frame update

    void DataInitial()
    {
        maxhealth = 100;
        health = maxhealth;
        attack_type = 1;

        ebd_1 = Enemy_1.damage;
        ebd_2 = Enemy_2.damage;
        ebd_3 = Enemy_3.damage;
        ebd_4 = Enemy_4.damage;
    }

    void ClassInitial()
    {
        animator = GetComponent<Animator>();
        myrigidbody = GetComponent<Rigidbody2D>();

        Enemy_1 = FindObjectOfType<Enemy_1>();
        Enemy_2 = FindObjectOfType<Enemy_2>();
        Enemy_3 = FindObjectOfType<Enemy_3>();
        Enemy_4 = FindObjectOfType<Enemy_4>();
    }

    void Start()
    {
        ClassInitial();
        DataInitial();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {

        if (collision .gameObject .layer == 6)
        {
            Debug.Log("collision");
            health -= collision_damage;
        }

        if (collision .gameObject .layer == 8)//Enemy_Bullets
        {
            switch (collision.gameObject.tag)
            {
                case "Enemy_bullet_1":
                BeHitted(ebd_1);
                Destroy(collision.gameObject);
                break;

                case "Enemy_bullet_2":
                BeHitted(ebd_2);
                Destroy(collision.gameObject);
                break;

                case "Enemy_bullet_3":
                BeHitted(ebd_3);
                Destroy(collision.gameObject);
                break;

                case "Enemy_bullet_4":
                BeHitted(ebd_4);
                Destroy(collision.gameObject);
                break;

                default:
                Debug.Log("UnSignedBulletTpye");
                break;
            }
        }

        if (collision.gameObject .tag == "Bullet_Plus")
        {
            attack_type++;
            if (attack_type > 3) attack_type = 3;
            SoundEffectManager.PlayAudioReload();
            Destroy(collision .gameObject);
        }

        if (collision .gameObject .tag == "Health_Plus")
        {
            health += health_recover;
            if (health > 100) health = 100; 
            Destroy(collision.gameObject);
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (!isdead)
        {
            Move();
            Shoot();
        }
        Dead();
        //SoundEffectManager.PlayAudioPlayer_Attack();
    }

    public void Move()
    {
        move_direction_x = Input.GetAxis("Horizontal");
        move_direction_y = Input.GetAxis("Vertical");
        if (!isdead)
        {
            myrigidbody.velocity = new Vector3(move_direction_x*velocity ,move_direction_y*velocity ,0);
            if (move_direction_x > 0) { animator.SetBool("TrunRight", true); animator.SetBool("TrunLeft", false); }
            else if (move_direction_x < 0) { animator.SetBool("TrunRight", false); animator.SetBool("TrunLeft", true);}
            else { animator.SetBool("TrunRight", false); animator.SetBool("TrunLeft", false); }
        }
    }

    public void Shoot()
    {
        switch (attack_type)
        {
            case 1:
                Shoot_1();    
            break;

            case 2:
                Shoot_2();
            break;

            case 3:
                Shoot_3();
            break;
        }
    }

    public void Shoot_1()
    {
        if (Time.time - timer > 0.2f)
        {
            timer = Time.time;
            Instantiate(Player_bullet,transform .position+correction_1 ,Quaternion.identity);
            SoundEffectManager.PlayAudioPlayer_Attack();
        }
    }

    public void Shoot_2()
    {
        if (Time.time - timer > 0.2f)
        {
            timer = Time.time;
            Instantiate(Player_bullet, transform.position + new Vector3 ( correction_2.x,correction_2.y,0), Quaternion.identity);
            Instantiate(Player_bullet, transform.position + new Vector3(-correction_2.x, correction_2.y, 0), Quaternion.identity);
            SoundEffectManager.PlayAudioPlayer_Attack();
        }
    }

    public void Shoot_3()
    {
        if (Time.time - timer > 0.2f)
        {
            timer = Time.time;
            Instantiate(Player_bullet, transform.position + new Vector3(correction_3.x, correction_3.y, 0), Quaternion.identity);
            Instantiate(Player_bullet, transform.position + correction_1, Quaternion.identity);
            Instantiate(Player_bullet, transform.position + new Vector3(-correction_3.x, correction_3.y, 0), Quaternion.identity);
            SoundEffectManager.PlayAudioPlayer_Attack();
        }
    }

    private void BeHitted(int damage)
    {
        SoundEffectManager.PlayAudioBeHitted();
        if (attack_type > 1)
        {
            attack_type--;
        }
        else if (attack_type == 1 && health >= 0)
        {
            health -= damage;
        }
    }

    private void Dead()
    {
        if (health <= 0)
        {
            health = 0;
            isdead = true;
            Dead_UI.SetActive(true);
            Time.timeScale = 0;
        }
    }
}

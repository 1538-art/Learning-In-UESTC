using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_2 : MonoBehaviour
{
    [Header("Class")]
    private Rigidbody2D rigidbody;
    public GameObject bullet;
    public GameObject Explosion;
    public GameObject Bullet_Plus;
    public GameObject Health_Plus;
    public Transform Blood;
    public ScoreManager scoreManager;
    public MyBullets playerBullets;

    [Header("Shoot")]
    public Vector2 speed;
    public Vector3 Correction;
    public int damage;

    [Header("Basic")]
    public float health;
    public float maxHealth;
    public int player_damage;
    public float lifetime;

    [Header("Reward")]
    public int score;

    float last_atk_time = -100;
    float life_timer;
    // Start is called before the first frame update
    void Start()
    {
        ClassInitial();
        DataInitial();
    }

    void ClassInitial()
    {
        scoreManager = FindObjectOfType<ScoreManager>();
        rigidbody = GetComponent<Rigidbody2D>();
        Blood = transform.GetChild(0);
        //playerBullets = FindObjectOfType<MyBullets>();
    }

    void DataInitial()
    {
        health = maxHealth;
        player_damage = playerBullets.Damage;
        rigidbody.velocity = speed;
    }

    // Update is called once per frame
    void Update()
    {
        Shoot();
        DeadAuto();
        Dead();
        BloodChange();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player_bullet")
        {
            health -= player_damage;
            Destroy(collision.gameObject);
        }
    }

    private void Dead()
    {
        if (health <= 0)
        {
            float i;
            i = UnityEngine.Random.Range(0f, 1f);
            if (i > 0.65f)
            {
                float j;
                j = UnityEngine.Random.Range(0f, 1f);
                if (j > 0.7) Instantiate(Health_Plus, transform.position, Quaternion.identity);
                else Instantiate(Bullet_Plus, transform.position, Quaternion.identity);
            }
            scoreManager.ChangeScore(score);
            SoundEffectManager.PlayAudioExplosion();
            Instantiate(Explosion, transform.position, Quaternion.identity);
            Destroy(gameObject);
        }
    }

    private void Shoot()//生成三行弹幕
    {
        if (Time.time - last_atk_time > 5f)
        {
            SoundEffectManager.PlayAudioEnemyShoot();
            last_atk_time = Time.time;
            for (int i = 0; i < 3; i++)
            {
                Instantiate(bullet, new Vector3(transform.position.x + Correction.x, transform.position.y + i*Correction.y, transform.position.z), Quaternion.identity);
                Instantiate(bullet, new Vector3(transform.position.x - Correction.x, transform.position.y + i*Correction.y, transform.position.z), Quaternion.identity);
            }
        }
    }

    private void DeadAuto()
    {
        life_timer += Time.deltaTime;
        if (life_timer > lifetime)
        {
            Destroy(gameObject);
        }
    }
    private void BloodChange()
    {
        Blood.localScale = new Vector3(health / maxHealth, 0.1f, 1);
        Debug.Log(health / maxHealth);
    }
}

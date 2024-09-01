using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_4 : MonoBehaviour
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
    public Vector3 Correction;
    public int damage;
    public int bullet_num;
    public float bullet_speed;
    public float StartAngle;
    public float EndAngle;
    public float AnglePerBullet;
    private float lastShootTime=-100;

    public Vector2 speed;

    [Header("Basic")]
    public float health;
    public float maxHealth;
    public int player_damage;
    public float lifetime;

    [Header("Reward")]
    public int score;

    float last_atk_time = -100;
    float life_timer = 0;
    int j;

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
        EndAngle = -StartAngle;
        AnglePerBullet = Mathf.Abs(EndAngle-StartAngle)/bullet_num;
        j = bullet_num;
    }

    // Update is called once per frame
    void Update()
    {
        Dead();
        DeadAuto();
        Shoot();
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
            if (i > 0.5f)
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

    private void DeadAuto()
    {
        life_timer += Time.deltaTime;
        if (life_timer > lifetime)
        {
            Destroy(gameObject);
        }
    }

    private void Shoot()
    {
        if (Time.time - last_atk_time > 5)
        {
            last_atk_time = Time.time;
            Debug.Log("bullet_num--");
            StartCoroutine("shoot");           
            bullet_num = j;
        }
    }

    IEnumerator shoot() 
    {
        Debug.Log("shoot");
        for (int i = 0; i < bullet_num; i++)
        {
            lastShootTime = Time.time;
            GameObject newbullet = Instantiate(bullet, transform.position, Quaternion.Euler(0, 0, StartAngle + i * AnglePerBullet));
            Rigidbody2D rb = newbullet.GetComponent<Rigidbody2D>();
            float tan_a = 0;
            float angle = newbullet.transform.rotation.eulerAngles.z;
            if (angle > 180f) angle -= 360f;
            tan_a = Mathf.Tan(Mathf.Deg2Rad * (90f - Mathf.Abs(angle)));
            if (angle > 0f) rb.velocity = bullet_speed * new Vector2(tan_a, -1f);
            else rb.velocity = bullet_speed * new Vector2(tan_a, 1);
            yield return new WaitForSeconds(0.25f);
        }
        yield return null;
    }

    private void BloodChange()
    {
        Blood.localScale = new Vector3(health / maxHealth, 0.1f, 1);
        Debug.Log(health / maxHealth);
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.TestTools;

public class EnemyGnerater : MonoBehaviour
{
    [Header("Class")]
    public GameObject Enemy_1;
    public GameObject Enemy_2;
    public GameObject Enemy_3;
    public GameObject Enemy_4;
    public ScoreManager ScoreManager;

    [Header("Data")]
    public int score;
    private float last_generate_time;
    private float genrate_time = 5f;

    private void Start()
    {
        ScoreManager = FindObjectOfType<ScoreManager>();
    }

    private void Update()
    {
        Gnerate();
    }

    void Gnerate()
    {
        if (Time.time-last_generate_time > genrate_time)
        { 
            score = ScoreManager.score;
            if (score < 1500)
            {
                float moverange = UnityEngine.Random.Range(-1f, 1f);
                transform.position = new Vector3(21 * moverange, 14, transform.position.z);
                Instantiate(Enemy_1, transform.position, Quaternion.Euler(0,0,180));
                last_generate_time = Time.time;
            }

            else if (score < 2500)
            {
                genrate_time = 4.5f;
                float moverange = UnityEngine.Random.Range(-1f, 1f);
                float type = UnityEngine.Random.Range(0f, 1f);
                transform.position = new Vector3(21 * moverange, 14, transform.position.z);
                if (type < 0.6) Instantiate(Enemy_1, transform.position, Quaternion.Euler(0, 0, 180));
                else Instantiate(Enemy_2, transform.position, Quaternion.Euler(0, 0, 180));
                last_generate_time = Time.time;
            }

            else if (score < 4500)
            {
                genrate_time = 4;
                float moverange = UnityEngine.Random.Range(-1f, 1f);
                float type = UnityEngine.Random.Range(0f, 1f);
                transform.position = new Vector3(21 * moverange, 14, transform.position.z);
                if (type < 0.4) Instantiate(Enemy_1, transform.position, Quaternion.Euler(0, 0, 180));
                else if (type < 0.75) Instantiate(Enemy_2, transform.position, Quaternion.Euler(0, 0, 180));
                else Instantiate(Enemy_3, transform.position, Quaternion.Euler(0, 0, 180));
                last_generate_time = Time.time;
            }

            else
            {
                genrate_time = 3;
                float moverange = UnityEngine.Random.Range(-1f, 1f);
                float type = UnityEngine.Random.Range(0f, 1f);
                transform.position = new Vector3(21 * moverange, 14, transform.position.z);
                if (type < 0.35) Instantiate(Enemy_1, transform.position, Quaternion.Euler(0, 0, 180));
                else if (type < 0.6) Instantiate(Enemy_2, transform.position, Quaternion.Euler(0, 0, 180));
                else if (type < 0.8) Instantiate(Enemy_3, transform.position, Quaternion.Euler(0, 0, 180));
                else Instantiate(Enemy_4, transform.position, Quaternion.Euler(0, 0, 180));
                last_generate_time = Time.time;
            }
        }   
    }
}

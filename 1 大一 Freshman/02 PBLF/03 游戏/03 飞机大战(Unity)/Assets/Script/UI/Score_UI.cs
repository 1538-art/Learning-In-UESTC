using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score_UI : MonoBehaviour
{
    public Text score_txt;
    void Start()
    {
        ScoreManager scoreManager = FindObjectOfType<ScoreManager>();
        scoreManager.ScoreChanged.AddListener(UpdateScore);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void UpdateScore(int score)
    {
        score_txt.text = "Score:" + score.ToString();
    }
}

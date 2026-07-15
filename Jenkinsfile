pipeline {
    agent {
        label 'cpp-agent'
    }

    stages {
        stage('Pull') {
            steps {
                checkout scm
            }
        }

        stage('Build C++') {
            steps {
                sh '''
                    set -e

                    mkdir -p build

                    g++ -std=c++20 \
                        *.cpp \
                        -Iinclude \
                        -o build/myapp
                '''
            }
        }

        stage('Save Artifact') {
            steps {
                archiveArtifacts(
                    artifacts: 'build/myapp',
                    fingerprint: true
                )
            }
        }

        // --- New Stage: Run Ansible Playbook ---
        stage('Deploy with Ansible') {
            steps {
                // Use the ansiblePlaybook step provided by the Ansible plugin [citation:2][citation:6]
                ansiblePlaybook(
                    playbook: './setup-server.yml', // Path to your playbook in the repo
                    inventory: './setup-server.yml'    // Path to your inventory file
                    credentialsId: 'ansible-ssh-key'      // ID of the SSH key credential in Jenkins
                    // Add other parameters as needed, e.g., extraVars, limit, etc. [citation:2]
                )
            }
        }
    }

    // --- New: Post-build Actions for Notifications ---
    post {
        // Define a reusable function for cleaner code [citation:7][citation:11]
        always {
            script {
                // Call the function defined below
                slackNotification(currentBuild.result)
            }
        }
    }
}

def slackNotification(String buildStatus = 'STARTED') {
    buildStatus = buildStatus ?: 'SUCCESS'
    def color = buildStatus == 'SUCCESS'  ? '#47ec05' :
                buildStatus == 'UNSTABLE' ? '#d5ee0d' :
                                            '#ec2805'

    // Construct a detailed message
    def msg = "${buildStatus}: Job '${env.JOB_NAME}' #${env.BUILD_NUMBER}\n${env.BUILD_URL}"

    // Send the notification via the Slack plugin [citation:3][citation:11]
    slackSend(color: color, message: msg)
}
